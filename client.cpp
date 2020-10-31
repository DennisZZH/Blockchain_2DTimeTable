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
    // Initializations
    client_id = cid;
    port_id = BASE_PORT + cid;
    // Initialize network connection with peers
    // This function call should initialize sockfd_tcp
    if (set_up_connection() < 0) {
        std::cerr<<"Error: Failed to set up connection in Client "<<client_id<<" !"<<std::endl;
        exit(0);
    }
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
    
    // Initialize Threads
    // Spawn a Thread for continously receiving applications from peer clients
    recv_thread = std::thread(&client::recv_application, this);
    std::cout<<"recv_thread is created!"<<std::endl;

    // Spawn a Thread for continously processing applications recved from peers
    proc_thread = std::thread(&client::proc_application, this);
    std::cout<<"proc_thread is created!"<<std::endl;
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

int client::set_up_connection() {
    // TODO
    return 0;
}

int client::garbage_collect() {
    // TODO
    return 0;
}

void client::recv_application() {
    // TODO
}

void client::proc_application() {
    // TODO
} 


int main(int argc, char* argv[]) {
    return 0;
}