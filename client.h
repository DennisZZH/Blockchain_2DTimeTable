#ifndef CLIENT_H
#define CLIENT_H

#include <cstdlib>
#include <iostream>
#include <list>
#include <queue>
#include <thread>
#include <mutex>
#include "parameters.h"
//#include "Msg.pb.h"

struct transaction_t{
    uint32_t sender_id;
    uint32_t recver_id;
    float amt;
    transaction_t(uint32_t sid, uint32_t rid, float amount) {
        sender_id = sid;
        recver_id = rid;
        amt = amount;
    }
};

class client {

public:
    client(uint32_t cid);
    ~client();

    uint32_t get_client_id() {return client_id;};

    int transfer_money(uint32_t rid, float amt);
    int send_application(uint32_t rid);
    float check_balance(uint32_t cid);

private:
    uint32_t client_id;
    int port_id;
    int sockfd_tcp;
    std::list<transaction_t> blockchain;
    float balance_table[MAX_CLIENT_SIZE];
    uint32_t timetable[TIME_TABLE_SIZE];
    uint32_t clocktime;
    //std::queue<application_msg_t> msg_buffer;

    // Thread safe Getter helper functions
    float get_balance(uint32_t cid);
    u_int32_t get_timetable(uint32_t j, uint32_t k);
    uint32_t get_clocktime() {return clocktime;};

    // Thread safe Setter helper functions
    void set_balance(uint32_t cid, float amt);
    void set_timetable(uint32_t j, uint32_t k, uint32_t t);
    void increase_clocktime();               // Increase its own clocktime by 1
    void add_to_blockchain(transaction_t &trans);   // Add a transaction to blockchain
    
    int set_up_connection();
    int garbage_collect();

    // Mutexes
    std::mutex clocktime_mutex;
    std::mutex timetable_mutex;
    std::mutex balance_table_mutex;
    std::mutex blockchain_mutex;

    // Threads
    std::thread recv_thread;                 // Thread for listening & recving application from peers
    std::thread proc_thread;                 // Thread for precessing recved application from peers                              

    // Thread Tasks
    void recv_application();                // Thread function for recving applications from peers
    void proc_application();                // Thread functon for processing applications recved from peers
};

#endif