#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include "client.h"
#include "parameters.h"
#include "utility.h"

#define TRANSFER_ARGS_NUM 2
#define MESSAGE_ARGS_NUM 1
#define BALANCE_ARGS_NUM 1

const char* usage = "Run the program by typing ./client <cid> where cid is within range [0, 2].";

inline void print_usage() {
    printf("%s\n", usage);
}

int main(int argc, char** argv) {

    if (argc != 2) {
        print_usage();
        exit(1);
    }

    int cid = atoi(argv[1]);
    if (cid < 0 || cid > 2) {
        std::cout << "Your input cid is out of the accepted range." << std::endl;
        print_usage();
        exit(1);
    }
    client c(cid);

    std::string input;
    while(true) {
        input.clear();
        std::getline(std::cin, input);
        std::stringstream ss(input);
        std::vector<std::string> args;
        while (ss.good()) {
            std::string arg = "";
            ss >> arg;
            args.push_back(arg);
        }
        
        std::string &cmd = args[0];
        if (cmd.compare("t") == 0 || cmd.compare("transfer") == 0) 
        {
            if (args.size() != TRANSFER_ARGS_NUM + 1) {
                std::cout << "Transfer command format is not correct." << std::endl;
                continue;
            }
            int recv_id = atoi(args[1].c_str());
            float amount = (float)atof(args[2].c_str());

            if (recv_id < 0 || recv_id > 2) {
                std::cout << "[main] Invalid recv_id. Please make sure the id is from 0 to 2." << std::endl;
                continue;
            }
            // Call the transfer transaction method.
            int status = c.transfer_money(recv_id, amount);
            switch (status) {
                case INSUFFICIENT_BALANCE_ERROR:
                    std::cout << "[main] Incorrect: Insufficient balance!" << std::endl;
                    break;
                case ILLEGAL_RECVER_ERROR:
                    std::cout << "[main] Incorrect: You cannot send money to your self!" << std::endl;
                    break;
                default:
                    std::cout << "[main] Success!" << std::endl; 
                    
            }
        }

        else if (cmd.compare("m") == 0 || cmd.compare("message") == 0) {
            if (args.size() != MESSAGE_ARGS_NUM + 1) {
                std::cout << "Message command format is not correct." << std::endl;
                continue;
            }
            int recv_id = atoi(args[1].c_str());
            if (recv_id < 0 || recv_id > 2) {
                std::cout << "[main] Invalid recv_id. Please make sure the id is from 0 to 2." << std::endl;
            }
            else if (c.send_application(recv_id) < 0) {
                std::cout << "[main] Incorrect: Fail to send application message!" << std::endl;
            }
            else {
                std::cout << "[main] Success: Message sent to client #" << recv_id << std::endl;
            }
        }

        else if (cmd.compare("b") == 0 || cmd.compare("balance") == 0) {
            if (args.size() != BALANCE_ARGS_NUM + 1) {
                std::cout << "Balance command format is not correct." << std::endl;
                continue;
            }
            int client_id = atoi(args[1].c_str());
            if (client_id < 0 || client_id > 2) {
                std::cout << "[main] Invalid recv_id. Please make sure the id is from 0 to 2." << std::endl;
            } else {
                std::cout << "[main] Balance = " << c.check_balance(client_id) << std::endl;
            }
        }

        else if (cmd.compare("d") == 0 || cmd.compare("debug") == 0) { 
            std::cout<<c.get_blockchain_str()<<std::endl;
            std::cout<<c.get_timetable_str()<<std::endl;
            std::cout<<c.get_balance_table()<<std::endl;
        }

        else {
            std::cout << "Wrong command, please input again!" << std::endl;
        }

    }

    return 0;
}