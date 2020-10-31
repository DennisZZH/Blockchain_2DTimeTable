#include "client.h"
#include "parameters.h"
#include "utility.h"

int main(int argc, char** argv) {

    if (argc != 2) {
        std::cerr << "Please input the current client id." << std::endl;
        exit(1);
    }

    int cid = atoi(argv[1]);
    client c(cid);
    while(true);
    return 0;
}