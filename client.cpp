#include <cstdlib>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "client.h"
//#include "Msg.pb.h"
#include "parameters.h"
#include "utility.h"

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

void client::increase_clocktime() {
    clocktime_mutex.lock();
    clocktime++;
    clocktime_mutex.unlock();
}

void client::add_to_blockchain(transaction_t &trans) {
    blockchain_mutex.lock();
    blockchain.push_back(trans);
    blockchain_mutex.unlock();
}

int client::transfer_money(uint32_t rid, float amt) {
    if (rid != client_id) {
        return ILLEGAL_SENDER_ERROR;
    }
    if (get_balance(client_id) < amt) {
        return INSUFFICIENT_BALANCE_ERROR;
    }
    increase_clocktime();
    transaction_t newtrans = transaction_t(client_id, rid, amt);
    add_to_blockchain(newtrans);
    set_balance(client_id, get_balance(client_id) - amt);
    set_timetable(client_id, client_id, clocktime);
    return 0;
}

int client::send_application(uint32_t rid) {
    // TODO
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

int client::garbage_collect() {
    // TODO
    return 0;
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
    // TODO
    uint8_t buffer[4096] = {0};
    while (!stop_flag) {
        // Receive logic here.
        int sock = clients_connected[id].socket;
        int size = read(sock, buffer, sizeof(buffer));
        if (size <= 0) {
            break;
        }
    }
    // If this thread stops for any reason.
    // Need to free the client socket.
    // close(clients_connected[id].socket);  // May not need this.
    std::cout << "[recv] client: " << id << " is exiting." << std::endl;
    close(clients_connected[id].socket);
    clients_connected[id].valid = false;
    // Don't need to deal with the thread here, after this function, the thread will quit.
}

void client::proc_application() {
    // TODO
}