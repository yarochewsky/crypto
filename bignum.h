#ifndef _BIG_NUM_H_
#define _BIG_NUM_H_

#include <stdio.h>
#include <inttypes.h>

#define BIT_LENGTH 64
#define BASE 10

/**
 * bignum - definition of a multi-precision
 *          integer, as an array of integers
 *          of length predefined (above), a sign/size integer
 *          (negative sizes represent a negative bignum),
 *          and a base. 
 * Notes: 
 *          (a) we store LSB at index 0 and count
 *          from right to left (MSB at size - 1)
 *          (b) we guarantee to calculate and store
 *          the minimum number of digits required
 *          to represent a number in the field size
 *          i.e. no leading zeroes
*/
typedef struct {
    int32_t size;
    uint32_t* limbs;
    uint32_t base;
} bignum;

/**
 * bignum_init - initializes a number with a size, base
 *               and populates limbs to 0. Pass in a negative
 *               size to get a negative number
 * @x : number to be initialized
 * @size : desired size of number
 * @base : base to be used for the number
 * Returns 1 on success or 0 on failure
*/
uint8_t bignum_init(bignum* x, int32_t size, uint32_t base);

/**
 * bignum_free - free resources associated with a number
 * @x : number for which resources will be freed
*/
void bignum_free(bignum* x);

/**
 * bignum_copy - replaces the value of a number with that of another
 * @dst : copy destination
 * @src : copy source
*/
void bignum_copy(bignum* dst, const bignum* src);

/**
 * bignum_negative - returns whether number is positive or negative
 * @x : number for which sign is to be determined 
*/
uint8_t bignum_negative(const bignum* x);


/**
 * bignum_size - returns size of number
 * @x : number for which size is to be determined
*/
uint32_t bignum_size(const bignum* x);

/**
 * bignum_addition - computes addition of two numbers
 * @x : first number to be added
 * @y : second number to be added
 * Returns addition result, or NULL on failure
*/
bignum* bignum_addition(const bignum* x, const bignum* y);

/**
 * bignum_subtraction - computes subtraction of two numbers
 * @x : number to be subtracted from
 * @y : number to subtract
 * Returns subtraction result, or NULL on failure
*/
bignum* bignum_subtraction(const bignum* x, const bignum* y);

/**
 * bignum_multiplication - computes multiplication of two numbers
 * @x : first number to be multiplied 
 * @y : second number to be multiplied 
 * Returns multiplication result, or NULL on failure
*/
bignum* bignum_multiplication(const bignum* x, const bignum* y);

/**
 * bignum_division - computes division of two numbers
 * @de : dividend
 * @dv : divisor 
 * @q : quotient as output parameter
 * @r : remainder as output parameter
 * Stores the quotient and remainder in the output parameters.
 * Returns 1 on success, or 0 on failure
*/
uint8_t bignum_division(const bignum* de, const bignum* dv, bignum* q, bignum* r);

/**
 * convert_base - converts a number to the new base
 * @target : number to be converted
 * @base_old : current base of the number
 * @base : base to convert the number to
 * @result : new base number stored as an array where each element
 *           is the i-th digit of the number
 * Returns length of new number on success, or -1 if pre-condition not satisfied,
 * i.e. target < 0 or base < 2
*/
int32_t convert_base(int32_t target, uint8_t base_old, uint8_t base,
                     uint32_t** result);

#endif
