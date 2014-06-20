/*
 * Garbage collector.
 * 
 * Author: Guido Tagliavini Ponce
 */

#ifndef __GC_H_INCLUDED__
#define __GC_H_INCLUDED__

#include <stdlib.h>
#include <stdint.h>
#include "list.h"
#include "trie.h"
#include "stack.h"
#include "utils.h"
#include "defines.h"
#include "timing.h"

/*
 * Initializes the GC.
 */
void init_gc(uint initial_free_cells, uint object_size);

/*
 * Frees all the resources used.
 */
void terminate_gc();

/*
 * Allocates a new object and returns a pointer to it.
 */
void *new();

void sweep();

void mark_std(cell *c);

void mark_sweep_std();

void mark_fast(trie *t, cell *c);

void mark_sweep_fast();

/*
 * Sets an object as a root.
 */
void set_root(void *object);

/*
 * Sets a pointer to an object to null.
 */
void set_null(void **object);

/*
 * Returns true iif the address in object corresponds to an object.
 */
bool is_pointer(void *object);

void fill_live_trie(trie *t);

/*
 * Prints information about the GC's status.
 */
void print_status();

#endif
