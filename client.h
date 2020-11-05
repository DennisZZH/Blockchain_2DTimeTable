#ifndef __CLIENT_H__
#define __CLIENT_H__

#include <cstdlib>
#include <iostream>
#include <list>
#include <queue>
#include <vector>
#include <thread>
#include <mutex>
#include "parameters.h"
#include "Msg.pb.h"

struct transaction_t{
    uint32_t sender_id;
    uint32_t recver_id;
    float amt;
    uint32_t clock;
    transaction_t(uint32_t sid, uint32_t rid, float amount, uint32_t t) {
        sender_id = sid;
        recver_id = rid;
        amt = amount;
        clock = t;
    }
};

struct client_info_t {
    int socket;
    bool valid;
    std::thread task;
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
    client_info_t clients_connected[MAX_CLIENT_SIZE] = {0};

    uint32_t clocktime;
    uint32_t timetable[TIME_TABLE_SIZE];
    std::list<transaction_t> blockchain;
    float balance_table[MAX_CLIENT_SIZE];
    std::queue<application_msg_t> msg_buffer;

    bool stop_flag = false;

    // Thread safe Getter helper functions
    float get_balance(uint32_t cid);
    u_int32_t get_timetable(uint32_t j, uint32_t k);
    void get_timetable_msg(timetable_msg_t* timetable_msg);
    std::string get_timetable_str();
    uint32_t get_clocktime() {return clocktime;};
    void get_transactions(uint32_t target_clock, std::vector<transaction_t> &log);  // Get qualified transactions
    application_msg_t pop_msg_buffer();

    // Thread safe Setter helper functions
    void set_balance(uint32_t cid, float amt);
    void set_timetable(uint32_t j, uint32_t k, uint32_t t);
    void increase_clocktime();                          // Increase its own clocktime by 1
    void add_to_blockchain(transaction_t &trans);       // Add a transaction to blockchain
    void push_msg_buffer(application_msg_t &app_msg);    // Push a application msg to msg_buffer

    int garbage_collect();
    int setup_server();                    // Setup the socket and ready to accept socket.
    

    // Mutexes
    std::mutex clocktime_mutex;
    std::mutex timetable_mutex;
    std::mutex balance_table_mutex;
    std::mutex blockchain_mutex;
    std::mutex msg_buffer_mutex;

    // Threads
    std::thread conn_thread;                    // Thread for connecting to the other two peers.
    std::thread wait_thread;                    // Thread for listening & accepting connections from peers.
    std::thread recv_thread;                    // Thread for listening & recving application from peers
    std::thread proc_thread;                    // Thread for precessing recved application from peers                              

    // Thread Tasks
    void setup_connections();                   // Setup the connections to connect to other clients.
    void wait_connections();                    // Thread function for listening & accepting connections. 
    void proc_application();                    // Thread functon for processing applications recved from peers
    void recv_application(int index);           // Thread function for recving applications from peers. Index is used for freeing the client slot.
};

#endif