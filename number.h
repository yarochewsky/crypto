#ifndef _NUMBER_H_
#define _NUMBER_H_

#include <stdio.h>
#include <inttypes.h>

#define BIT_LENGTH 64

/**
 * bigint - definition of a multi-precision
 *          integer, as an array of integers
 *          of length predefined (above)
*/
typedef uint32_t bigint[BIT_LENGTH];

/**
 * big_init - initializes a number
 * @x : number to be initialized
*/
void big_init(bigint* x);

/**
 * big_free - free resources associated with a number
 * @x : number for which resources will be freed
*/
void big_free(bigint* x);

/**
 * big_copy - replaces the value of a number with that of another
 * @dst : copy destination
 * @src : copy source
*/
void big_copy(bigint* dst, const bigint* src);

/**
 * big_bitlen - returns the smallest number of bits necessary to represent x
 * @x : number to be represented
*/
uint32_t big_bitlen(const bigint* x);

/**
 * big_size - returns the total size of the number in bytes
 * @x : number for which size is to be returned
*/
uint32_t big_size(const bigint* x);

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
