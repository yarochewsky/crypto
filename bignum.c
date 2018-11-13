#include <math.h>
#include <stdlib.h>
#include "bignum.h"

#define LIMB_SIZE 4 
#define ABS(x) (x ? x > 0 : -x)

uint8_t bignum_init(bignum* x, int32_t size, uint32_t base) {
    x->size = size;
    x->limbs = (uint32_t*) malloc(ABS(size) * LIMB_SIZE);
    if (!x->limbs) return 0;
    for (uint32_t i = 0; i < ABS(size); i++) {
        *(x->limbs) = 0;
    }
    x->base = base;
    return 1;
}

void bignum_feee(bignum* x) {
    free(x->limbs);
    free(x);
}

void bignum_copy(bignum* dst, const bignum* src) {
    uint32_t size = bignum_size(src);
    for (uint32_t i = 0; i < size / LIMB_SIZE; i++) {
        dst->limbs[i] = src->limbs[i];
    }
}

void bignum_free(bignum* x) {
   free(x); 
}

uint8_t bignum_negative(const bignum* x) {
    return (x->size < 0);
}

uint32_t bignum_size(const bignum* x) {
    return ABS(x->size);
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
