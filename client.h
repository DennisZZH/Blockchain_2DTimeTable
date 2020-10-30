#ifndef CLIENT_H
#define CLIENT_H

#include <cstdlib>
#include <iostream>
#include <list>
#include <queue>
#include <thread>
#include <mutex>
#include <parameters.h>
#include "Msg.pb.h"

typedef struct {
    uint32_t sender_id;
    uint32_t recver_id;
    float amt;
} transaction_t;

class client {

public:
    client(uint32_t client_id);
    ~client();

    uint32_t get_client_id() {return client_id;};
    float get_balance(uint32_t client_id);
    u_int32_t get_timetable(uint32_t j, uint32_t k);
    uint32_t get_clocktime() {return clocktime;};

    void set_balance(uint32_t client_id, float amt);
    void set_timetable(uint32_t j, uint32_t k, uint32_t time);
    void increase_clocktime();                                          // Increase its own clocktime by one

    int transfer_money(uint32_t recver_id, float amt);
    int send_application(uint32_t recver_id);
    float check_balance(uint32_t client_id);

private:
    uint32_t client_id;
    int port_id;
    int sockfd_tcp;
    std::list<transaction_t> blockchain;
    float balance_table[MAX_CLIENT_SIZE];
    uint32_t timetable[TIME_TABLE_SIZE];
    uint32_t clocktime;
    std::queue<application_msg_t> msg_buffer;

    int set_up_connection();
    int garbage_collect();

    // Mutexs
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