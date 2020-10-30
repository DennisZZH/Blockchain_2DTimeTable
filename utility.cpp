#include <cmath>
#include <cstdlib>
#include "utility.h"
#include "parameters.h"

/**
 * @brief Generate a random 32 bit integer within [1, 2, .... range]
 * 
 * @param range the random number generated.
 * @return uint32_t 
 */
uint32_t random_uint32(uint32_t range) {
    return ceil((double)rand()/RAND_MAX * range);
}

