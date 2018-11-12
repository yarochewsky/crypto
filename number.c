#include <math.h>
#include <stdlib.h>
#include "number.h"

int32_t convert_base(int32_t target, uint8_t base_old, uint8_t base, 
                     uint32_t** result) {
    if (target < 0 || base < 2) return -1;
    uint32_t i = 0;
    uint32_t x = target;
    int32_t q = floor(x / base);
    // length of new number
    uint32_t length = (log(target) / log(base)) + 1;
    // allocate array for new number
    uint32_t* number = (uint32_t*) malloc(length);
    // a0 a1 a2 ... a(length - 1) --> length numbers
    // each number is a(length - 1 - i)
    *(number + (length - 1)) = x - q * base;
    while (q > 0) {
        i++;
        x = q;
        q = floor(x / base);
        *(number + length - 1 - i) = x - q * base;
    }
    *result = number; 
    return length;
}
