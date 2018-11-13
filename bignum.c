#include <math.h>
#include <stdlib.h>
#include "bignum.h"

#define LIMB_SIZE 4 
#define ABS(x) (x ? x > 0 : -x)
#define MAX(x, y) (x ? x >= y : y)

/**
 * bignum_util_subtraction - computes subtraction of two numbers
 * @x : number to be subtracted from
 * @y : number to subtract 
 * @result : output parameter to store result
 * Stores the result of the subtraction on the output parameter result,
 * and returns the carry of the operation
*/
static int32_t bignum_util_subtraction(const bignum* x, const bignum* y,
                                       bignum* result); 

/**
 * bignum_minimize_size - computes the minimum number of bits required to store
 *                        a number (i.e no leading zeroes)
 * @x : number for which optimal size is to be computed
 * Returns the minimum number of bits
*/
static uint32_t bignum_minimize_size(const bignum* x);
 
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

void bignum_free(bignum* x) {
    free(x->limbs);
    free(x);
}

void bignum_copy(bignum* dst, const bignum* src) {
    uint32_t size = bignum_size(src);
    for (uint32_t i = 0; i < size / LIMB_SIZE; i++) {
        dst->limbs[i] = src->limbs[i];
    }
}

uint8_t bignum_negative(const bignum* x) {
    return (x->size < 0);
}

uint32_t bignum_size(const bignum* x) {
    return ABS(x->size);
}

bignum* bignum_addition(const bignum* x, const bignum* y) {
    // we must insist that bases be the same for addition
    if (x->base != y->base) return NULL;
    uint8_t carry = 0;
    // allocate resources for addition result
    bignum* result = (bignum*) malloc(sizeof(bignum));
    if (!result) return NULL;
    uint32_t len = MAX(bignum_size(x), bignum_size(y));
    // size is at most len + 1. Update later as needed
    // initialize resources for result
    bignum_init(result, len + 1, x->base); 
    for (uint32_t i = 0; i < len; i++) {
        uint32_t operation = (x->limbs[i] + y->limbs[i] + carry);
        result->limbs[i] = operation % x->base;
        if (operation < x->base) { 
            carry = 0;
        } else {
            carry = 1;
        }
    }
    // place carry as last digit
    result->limbs[len] = carry;
    // update size if we didn't use carry, as promised
    if (!carry) { result->size--; }
    // we're done
    return result;
}

bignum* bignum_subtraction(const bignum* x, const bignum* y) {
    if (x->base != y->base) return NULL;
    bignum* result = (bignum*) malloc(sizeof(bignum));
    if (!result) return NULL;
    uint32_t len = MAX(bignum_size(x), bignum_size(y));
    bignum_init(result, len, x->base);
    int32_t carry = bignum_util_subtraction(x, y, result);
    if (carry < 0) {
        // re-run subtraction with x = 0 and y = result
        bignum* x_0 = (bignum*) malloc(sizeof(bignum));
        if (!x_0) {
            free(result);
            return NULL;
        }
        bignum* output = (bignum*) malloc(sizeof(bignum));
        if (!output) {
            free(result);
            free(x_0);
            return NULL;
        }
        bignum_init(x_0, len, x->base);
        bignum_util_subtraction(x_0, result, output);
        // update size and sign as well -> here we already
        // now that the number is negative, since the carry was negative
        output->size = -1 * bignum_minimize_size(output);
        free(x_0);
        free(result);
        return output;
    }
    // update size
    result->size = bignum_minimize_size(result);
    return result;
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

static int32_t bignum_util_subtraction(const bignum* x, const bignum* y,
                                       bignum* result) {
    int32_t carry = 0;
    uint32_t len = MAX(bignum_size(x), bignum_size(y));
    for (uint32_t i = 0; i < len; i++) {
        int32_t operation = (x->limbs[i] - y->limbs[i] + carry);
        result->limbs[i] = operation % x->base;
        if (operation >= 0) {
            carry = 0;
        } else {
            carry = -1;
        }
    }
    return carry;
}

static uint32_t bignum_minimize_size(const bignum* x) {
    uint32_t size = BIT_LENGTH;
    for (uint32_t i = BIT_LENGTH; i > 0; i++) {
        if (x->limbs[i] == 0) { 
            size--;
        } else {
            return size;
        }
    }
    return size;
}
 
