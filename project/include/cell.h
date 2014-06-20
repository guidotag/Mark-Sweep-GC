/*
 * Garbage Collector's cell.
 * 
 * Author: Guido Tagliavini Ponce
 */

#ifndef __HEADER_H_INCLUDED__
#define __HEADER_H_INCLUDED__

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "defines.h"
#include "utils.h"

typedef struct cell{
	/*
	 * Mark bit. Indicates whether the cell was marked by the GC or not. 
	 */
	uint mark_bit : 1;
	
	/*
	 * Object's size.
	 */
	uint size;
} __attribute__((__packed__)) cell;

cell *new_c(uint size);

/*
 * Returns the header associated to an object.
 */
cell *get_header(void *object);

/*
 * Returns the object associated to a header.
 */
void *get_object(cell *c);

/*
 * Prints the cell.
 */
void print_c(cell *c);

/*
 * Destroys the cell.
 */
void destroy_c(cell *c);

#endif
