#ifndef _NUMBER_H_
#define _NUMBER_H_

#include <stdio.h>
#include <inttypes.h>

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
