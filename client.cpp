#include <cstdlib>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <vector>
#include <list>
#include <queue>
#include <algorithm>
#include "client.h"
#include "Msg.pb.h"
#include "parameters.h"
#include "utility.h"
#include <sstream>

client::client(uint32_t cid) {
    // Note: cid should be within 0 to 2
    if (cid >= CLIENT_NUM_MAX) {
        std::cerr << "The id number should be between: 0 to " << CLIENT_NUM_MAX - 1 << std::endl;
        exit(1); 
    }
    // Initializations
    client_id = cid;
    port_id = SERVER_BASE_PORT + cid;
    // Initialize everyone to have $10
    for (int i = 0; i < MAX_CLIENT_SIZE; i++) {
        balance_table[i] = 10.0;
    }
    // Initialize timetable to all 0s
    for (int i = 0; i < TIME_TABLE_SIZE; i++) {
        timetable[i] = 0;
    }
    // Initialize clocktime to 0
    clocktime = 0;
    
    // Start the server service
    if (setup_server()) {
        std::cerr << "[client init] Failed to setup the server." << std::endl;
    }

    // Initialize Threads
    // Spawn a Thread for continously receiving applications from peer clients
    conn_thread = std::thread(&client::setup_connections, this);
    std::cout << "[client init]conn_thread is created!" << std::endl;
    
    wait_thread = std::thread(&client::wait_connections, this);
    std::cout << "[client init]wait_thread is created!" << std::endl;

    // Spawn a Thread for continously processing applications recved from peers
    proc_thread = std::thread(&client::proc_application, this);
    std::cout<<"[client init]proc_thread is created!" << std::endl;
}

client::~client() {
    // Join threads
    recv_thread.join();
    proc_thread.join();
    //  Close socket
    close(sockfd_tcp);
}

float client::get_balance(uint32_t cid) {
    balance_table_mutex.lock();
    float curr_balance = balance_table[cid];
    balance_table_mutex.unlock();
    return curr_balance;
}

u_int32_t client::get_timetable(uint32_t j, uint32_t k) {
    timetable_mutex.lock();
    u_int32_t curr_t = timetable[MAX_CLIENT_SIZE * j + k];
    timetable_mutex.unlock();
    return curr_t;
}

/**
 * @brief Deprecated function. Replaced by get_timetable_msg();
 * 
 * @return std::string 
 */
std::string client::get_timetable_str(){
    std::string timetable_str = "";
    timetable_mutex.lock();
    for (int i = 0; i < TIME_TABLE_SIZE; i++) {
        timetable_str += timetable[i];
    }
    timetable_mutex.unlock();
    return timetable_str;
}

/**
 * @brief Pass in a pointer of the timetable object and this function will help you fill the current timetable data.
 * 
 * @param timetable_msg a pointer of the timetable_msg_t object.
 */
void client::get_timetable_msg(timetable_msg_t* timetable_msg) {
    timetable_mutex.lock();
    for (int i = 0; i < TIME_TABLE_SIZE; i++) {
        timetable_msg->add_time(timetable[i]);
    }
    timetable_mutex.unlock();
}

void client::get_transactions(uint32_t target_clock, std::vector<transaction_t> &log) {
    // Get all transactions t such that Timetable[k, node(t)] < time(t)
    for (auto it = blockchain.begin(); it != blockchain.end(); it++) {
        if (it->clock > target_clock) {
            log.push_back(*it);
        }
    }
}

application_msg_t client::pop_msg_buffer() {
    msg_buffer_mutex.lock();
    application_msg_t tmp = msg_buffer.front();        
    msg_buffer.pop();
    msg_buffer_mutex.unlock();
    return tmp;
}

void client::set_balance(uint32_t cid, float amt) {
    balance_table_mutex.lock();
    balance_table[cid] = amt;
    balance_table_mutex.unlock();
}

void client::set_timetable(uint32_t j, uint32_t k, uint32_t t) {
    timetable_mutex.lock();
    timetable[MAX_CLIENT_SIZE * j + k] = t;
    timetable_mutex.unlock();
}

void client::increase_clocktime() {                                     // REVIEW: Should also increase timetable? Double check 132
    clocktime_mutex.lock();
    clocktime++;
    clocktime_mutex.unlock();
}

void client::add_to_blockchain(transaction_t &trans) {
    blockchain_mutex.lock();
    blockchain.push_back(trans);
    blockchain_mutex.unlock();
}

void client::push_msg_buffer(application_msg_t &app_msg) {
    msg_buffer_mutex.lock();
    msg_buffer.push(app_msg);
    msg_buffer_mutex.unlock();
}

int client::transfer_money(uint32_t rid, float amt) {
    if (rid == client_id) {
        return ILLEGAL_RECVER_ERROR;
    }
    if (get_balance(client_id) < amt) {
        return INSUFFICIENT_BALANCE_ERROR;
    }
    increase_clocktime();
    transaction_t newtrans = transaction_t(client_id, rid, amt, get_clocktime());
    add_to_blockchain(newtrans);
    set_balance(client_id, get_balance(client_id) - amt);
    set_balance(rid, get_balance(rid) + amt);
    set_timetable(client_id, client_id, clocktime);
    return 0;
}

int client::send_application(uint32_t rid) {
    // Piggyback all transactions t such that Timetable[k, node(t)] < time(t)
    std::vector<transaction_t> trans_log;
    uint32_t target_clock = get_timetable(rid, client_id);
    get_transactions(target_clock, trans_log);                                  // REVIEW: Double check this function

    // Include all the info and create a application_msg_t
    application_msg_t new_application;
    transaction_msg_t* tran_ptr;
    new_application.set_sender_id(client_id);

    // Add the timetable into the application_msg
    timetable_msg_t *timetable = new timetable_msg_t();
    new_application.set_allocated_timetable(timetable);
    get_timetable_msg(timetable);
    
    for (auto t : trans_log) {
        tran_ptr = new_application.add_log();
        tran_ptr->set_sender_id(t.sender_id);
        tran_ptr->set_recver_id(t.recver_id);
        tran_ptr->set_amt(t.amt);
        tran_ptr->set_clock(t.clock);
    }
    // Send out the application
    std::string message = new_application.SerializeAsString();
    const char* message_str = message.c_str();
    HEADER_TYPE transfer_size = htonl(new_application.ByteSizeLong());
    uint8_t* transfer_str = new uint8_t[transfer_size + HEADER_SIZE];
    memcpy(transfer_str, &transfer_size, HEADER_SIZE);
    memcpy(transfer_str + HEADER_SIZE, message_str, strlen(message_str));

    // DEBUG: Need to check if the byte size is the same as the strlen:
    std::cout << "[send_application debug] byte count: " << new_application.ByteSizeLong() << std::endl;
    std::cout << "[send_application debug] strlen: " << strlen(message_str) << std::endl;

    if (!clients_connected[rid].valid) {
        std::cerr << "[send_application] The connection to the receiver is lost. " << strlen(message_str) << std::endl;
        delete [] transfer_str;
        return -1;
    }
    
    write(clients_connected[rid].socket, message_str, transfer_size + HEADER_SIZE);
    delete [] transfer_str;
    
    return 0;
}

float client::check_balance(uint32_t cid) {
   return get_balance(cid);
}

int client::setup_server() {
    sockfd_tcp = socket(AF_INET, SOCK_STREAM, 0);
    int flag;
    if (setsockopt(sockfd_tcp, SOL_SOCKET, SO_REUSEPORT, &flag, sizeof(flag)) < 0) {
        std::cerr << "[setup_server] Failed to set the socket options." << std::endl;
        exit(1);
    }
    sockaddr_in server_addr = {0};
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(CLIENT_IP);
    server_addr.sin_port = htons(SERVER_BASE_PORT + client_id);

    if (bind(sockfd_tcp, (sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "[setup_server] Failed to bind the socket." << std::endl;
        exit(1);
    }

    if (listen(sockfd_tcp, CLIENT_NUM_MAX * 2) < 0) {
        std::cerr << "[setup_server] Failed to listen the port." << std::endl;
        exit(1);
    }

    // Start client recycler thread
    return 0;
}

/**
 * @brief Connects to other peers' server services. Note that each client only try to treat the peers with lower IDs as servers.
 * 
 */
void client::setup_connections() {
    while (!stop_flag) {
        for (int id = 0; id < client_id; id++) {
            if (clients_connected[id].valid == false) {
                int sockfd = socket(AF_INET, SOCK_STREAM, 0);
                int flag;
                if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEPORT, &flag, sizeof(flag)) < 0) {
                    std::cerr << "[setup_server] Failed to set the socket options." << std::endl;
                    exit(1);
                }

                sockaddr_in self_addr = {0};
                self_addr.sin_family = AF_INET;
                self_addr.sin_addr.s_addr = inet_addr(CLIENT_IP);
                self_addr.sin_port = htons(CLIENT_BASE_PORT + client_id + id);       // Stupid way to avoid port conflicts.
                
                if (bind(sockfd, (sockaddr*) &self_addr, sizeof(self_addr)) < 0) {
                    std::cerr << "[setup_connections] Failed to bind self address." << std::endl;
                    close(sockfd);

                    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
                    continue;
                }
                
                sockaddr_in server_addr = {0};
                server_addr.sin_family = AF_INET;
                server_addr.sin_addr.s_addr = inet_addr(CLIENT_IP);
                server_addr.sin_port = htons(SERVER_BASE_PORT + id);
                
                if (connect(sockfd, (sockaddr*) &server_addr, sizeof(sockaddr_in)) < 0) {
                    std::cerr << "[setup_connections] Failed to connect the peer (server): " << id << std::endl;
                    close(sockfd);

                    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
                    continue;
                }

                try { 
                    clients_connected[id].task.join();
                } catch(...) {};  
                clients_connected[id].valid = true;
                clients_connected[id].socket = sockfd;
                clients_connected[id].task = std::thread(&client::recv_application, this, id);
                std::cout << "[setup_connections] Connected to " << id << std::endl;
            }
        }
    }
    std::cerr << "[setup_connections] Exited." << std::endl;
}

void client::wait_connections() {
    while (!stop_flag) {
        sockaddr_in peer_addr = {0};
        socklen_t peer_addr_size = sizeof(peer_addr);
        int peer_socket = accept(sockfd_tcp, (sockaddr*) &peer_addr, &peer_addr_size);
        if (peer_socket < 0) {
            std::cout << "[wait_connections] Failed to accept client." << std::endl;
            continue;
        }

        int peer_port_num = ntohs(peer_addr.sin_port);
        int peer_id = peer_port_num - CLIENT_BASE_PORT - client_id;
        std::cout << "[wait_connections] Accepted connection from client: " << peer_id << std::endl;
        
        if (clients_connected[peer_id].valid == false) {
            try { 
                clients_connected[peer_id].task.join();
            } catch(...) {};  
            clients_connected[peer_id].valid = true;
            clients_connected[peer_id].socket = peer_socket;
            clients_connected[peer_id].task = std::thread(&client::recv_application, this, peer_id);
        } else {
            std::cout << "[wait_connections] Couldn't find empty client_info socket." << std::endl;
            close(peer_socket);
        }
    }
}

void client::recv_application(int id) {
    // Keep listening to peers 
    // Recv an application_msg_t
    // Push it into msg_buffer
    // Note: use Thread Safe method push_msg_buffer() to push into msg_buffer
    while (!stop_flag) {
        // Receive logic here.
        int sock = clients_connected[id].socket;
        HEADER_TYPE receive_size = 0;
        
        // Make sure the socket is still valid.
        if (!clients_connected[id].valid)
            break;

        int size = read(clients_connected[id].socket, &receive_size, HEADER_SIZE);
        if (size <= 0) {
            std::cout << "[recv_application] Connection is lost." << std::endl;
            break;
        } else if (size < HEADER_SIZE) {
            std::cout << "[recv_application] Received broken header." << std::endl;
            continue;
        }   

        // Parse the payload size in bytes
        receive_size = ntohl(receive_size);
        uint8_t *message = new uint8_t[receive_size];
        
        size = read(clients_connected[id].socket, message, receive_size);
        if (size <= 0) {
            std::cout << "[recv_application] Connection is lost." << std::endl;
            delete [] message;
            break;
        } else if (size < receive_size) {
            std::cout << "[recv_application] Received broken body." << std::endl;
            delete [] message;
            continue;
        } 

        // Start parsing the message.
        application_msg_t application_message;
        application_message.ParseFromArray(message, receive_size);
        delete [] message;
        
        push_msg_buffer(application_message);
        std::cout << "[recv_application] Received app and saved." << std::endl;
    }
    // If this thread stops for any reason.
    // Need to free the client socket.
    // close(clients_connected[id].socket);  // May not need this.
    std::cout << "[recv_application] client: " << id << " is exiting." << std::endl;
    close(clients_connected[id].socket);
    clients_connected[id].valid = false;
    // Don't need to deal with the thread here, after this function, the thread will quit.
}

void client::proc_application() {
    while (!stop_flag) {
        // Pop an application from msg_buffer
        if (msg_buffer.size() == 0) {
            // If the message buffer is empty, then don't pop.
            continue;
        }
        application_msg_t curr_application = pop_msg_buffer();

        // Get the Timetable and transactions from that application
        uint32_t sid = curr_application.sender_id();
        uint32_t timetable_recv[TIME_TABLE_SIZE];

        if (curr_application.timetable().time_size() != TIME_TABLE_SIZE) {
            std::cerr << "[proc_application] Application contains invalid timetable info." << std::endl;
            continue;
        }
        
        // Update timetable.
        for (int i = 0; i < TIME_TABLE_SIZE; i++) {
            timetable_recv[i] = curr_application.timetable().time(i);       
        }
        
        // Parse the transactions_log
        std::vector<transaction_t> trans_log;
        for (int i = 0; i < curr_application.log_size(); i++) {             
            const transaction_msg_t& tran_msg = curr_application.log(i);
            trans_log.push_back(transaction_t(tran_msg.sender_id(), tran_msg.recver_id(), tran_msg.amt(), tran_msg.clock()));
        }
        // Incorporate all new transactions into local blockchain
        for (auto t : trans_log) {                                              
            if (t.clock > get_timetable(client_id, t.sender_id)) {              // REVIEW: Only add to the local queue when this client doesn't know the sender's event.
                add_to_blockchain(t);
                set_balance(t.sender_id, get_balance(t.sender_id) - t.amt);                                           
                set_balance(t.recver_id, get_balance(t.recver_id) + t.amt);       // REVIEW: Set balance.
            }
        }

        // Update Timetable so that, (1) Max of all elemets (2) Max of clocktimes in local ith row and remote kth row
        for (int row = 0; row < MAX_CLIENT_SIZE; row++) {
            for (int col = 0; col < MAX_CLIENT_SIZE; col++) {
                if (row == client_id) {
                    set_timetable(row, col, std::max(get_timetable(row, col), timetable_recv[sid * MAX_CLIENT_SIZE + col]));    // REVIEW: Double Check.
                }
                set_timetable(row, col, std::max(get_timetable(row, col), timetable_recv[row * MAX_CLIENT_SIZE + col]));
            }
        }
        // Garbage collect local blockchain from any records corresponding to transaction t such that
        // For all sites j, Timetable[j, node(t)] >= time(t)
        garbage_collect();
    }
}

int client::garbage_collect() {
    blockchain_mutex.lock();                                                    // REVIEW: Blockchain delete operation needs synchronization.
    for (auto it = blockchain.begin(); it != blockchain.end(); it++) {
        uint32_t sid = it->sender_id;
        uint32_t clock = it->clock;
        bool flag = true;
        for (int i = 0; i < MAX_CLIENT_SIZE; i++) {
            if (get_timetable(i, sid) < clock) {
                flag = false;
                break;
            }  
        }
        if (flag) {
            blockchain.erase(it);
        }
    }
    blockchain_mutex.unlock();
    return 0;
}