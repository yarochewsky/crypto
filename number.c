#include <math.h>
#include <stdlib.h>
#include "number.h"

uint32_t big_size(const bigint* x) {
    const bigint* ref = x;
    uint32_t size = 0;
    while (ref) {
        size++; 
        ref++;
    }
    return size * sizeof(*(x));
}

void big_copy(bigint* dst, const bigint* src) {
    uint32_t size = big_size(src);
    for (uint32_t i = 0; i < size / sizeof(*(src)); i++) {
        *(*dst + i) = *(*src + i); 
    }
}

void big_free(bigint* x) {
    free(x);
}

int32_t convert_base(int32_t target, uint8_t base_old, uint8_t base, 
                     uint32_t** result) {
    if (target < 0 || base < 2) return -1;
    uint32_t i = 0;
    uint32_t x = target;
    int32_t q = floor(x / base);
    uint32_t length = (log(target) / log(base)) + 1;
    uint32_t* number = (uint32_t*) malloc(length);
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
