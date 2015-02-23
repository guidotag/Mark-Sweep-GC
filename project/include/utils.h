/*
 * Utility library.
 * 
 * Author: Guido Tagliavini Ponce
 */

#ifndef __UTILS_H__
#define __UTILS_H__

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "defines.h"

#define ERR(label, val) 	printf("[DEBUG] " #label " : %i\n", val)
#define MAX(x, y) 			(((x) > (y)) ? (x) : (y))

/*
 * Returns the first fixed characters of the representation of n in radix base.
 * 
 * If fixed is greater than the number of characters needed to represent
 * n in radix base, then the function will add a number of leading zeros
 * to the representation to make it fixed characters long.
 */
char *to_base(unsigned long long n, uint base, uint fixed);

/*
 * Returns the length of n's representation in radix base.
 */
uint length_base(unsigned long long n, uint base);

uint _log(unsigned long long n, uint base);

uint _ceil(float x);

/*
 * Returns an integer random number between a and b.
 * 
 * To make it work randomly, put srand(time(NULL)) at the beggining of the program execution.
 */
int _random(int a, int b);

/*
 * Prints a complete line with the separator sep.
 */
void print_sep(char sep);

#endif
