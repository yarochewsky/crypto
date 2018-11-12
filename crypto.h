#include <inttypes.h>

#ifndef _CRYPTO_H_
#define _CRYPTO_H_

// Miller-Rabin primality testing for small integers
// n : target number to be tested
// k : number of iterations for the algorithm
// Returns 1 for prime, 0 for composite, -1 on failure
int8_t miller_rabin(uint32_t n, uint8_t k);

#endif
