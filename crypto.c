#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "crypto.h"

// factors the number n to be written as
// n - 1 = (2^r) * m, where r,m are returned
// as output parameters.
// Returns 1 on success, or 0 if n is even
static uint8_t factor_2(uint32_t n, uint32_t* m, uint16_t* r);

// raises n to the power of x
uint32_t pow_int(uint32_t n, uint32_t m);

int8_t miller_rabin(uint32_t n, uint8_t k) {
    if (n == 1) return 0;
    if (n == 2) return 1;
    uint32_t m;
    uint16_t r;
    if (factor_2(n, &m, &r)) {
        uint32_t a, x;
        for (uint8_t i = 0; i < k; i++) {
            a = (rand() % (n - 4)) + 2; 
            x = pow_int(a, m) % n;
            if (x == 1 || x == n - 1) continue;
            for (uint8_t j = 0; j < r - 1; j++) {
                x = (x * x) % n;
                if (x == 1) return 0;
                if (x == n - 1) continue; 
            }
        }
        return 1;
    }
    return 0;
}

static uint8_t factor_2(uint32_t n, uint32_t* m, uint16_t* r) {
    // n is even, we can't divide n - 1 by 2
    if (n % 2 == 0) return 0;
    uint16_t power_2 = 0;
    n = n - 1;
    while (n % 2 == 0) {
        power_2++;
        n /= 2;
    }
    *r = power_2;
    *m = n;
    return 1;
} 

uint32_t pow_int(uint32_t n, uint32_t m) {
    if (m == 0) return 1;
    if (m == 1) return n;
    return n * pow_int(n, m - 1); 
}
