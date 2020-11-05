#pragma once

/**
 * @brief The upper bound of the communication delay in seconds.
 * 
 */
#define COMM_DELAY_MAX      5

/**
 * @brief Communication format: [Bytes to transfer][Payload managed by protobuf]
 */
#define HEADER_TYPE     uint32_t
#define HEADER_SIZE     sizeof(HEADER_TYPE)

/**
 *  Communication related parameters
 */
#define CLIENT_IP           "127.0.0.1"
#define SERVER_BASE_PORT    8000
#define CLIENT_BASE_PORT    8010
#define CLIENT_NUM_MAX      3

/** @Insufficient balance error flag.
* Client throw this flag when user trying to send an amt greater than its balance
*/
#define INSUFFICIENT_BALANCE_ERROR  -1
#define ILLEGAL_RECVER_ERROR -2

/**
 *  Size related parameters 
 */
#define MAX_CLIENT_SIZE	3
#define TIME_TABLE_SIZE 3 * 3




