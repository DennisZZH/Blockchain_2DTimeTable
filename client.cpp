#include <cstdlib>
#include <iostream>

#include "client.h"
#include "Msg.pb.h"
#include "parameters.h"

client::client(uint32_t client_id) {

}

client::~client() {

}

float client::get_balance(uint32_t client_id) {
    // TODO
    return 0.0;
}

u_int32_t client::get_timetable(uint32_t j, uint32_t k) {
    // TODO
    return 0;
}

void client::set_balance(uint32_t client_id, float amt) {
    // TODO
}

void client::set_timetable(uint32_t j, uint32_t k, uint32_t time) {
    // TODO
}

void client::increase_clocktime() {
    // TODO
}                                

int client::transfer_money(uint32_t recver_id, float amt) {
    // TODO
    return 0;
}

int client::send_application(uint32_t recver_id) {
    // TODO
    return 0;
}

float client::check_balance(uint32_t client_id) {
    // TODO
    return 0.0;
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