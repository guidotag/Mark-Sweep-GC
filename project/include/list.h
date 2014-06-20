/*
 * Singly linked list data structure.
 * 
 * Author: Guido Tagliavini Ponce
 */

#ifndef __LIST_H_INCLUDED__
#define __LIST_H_INCLUDED__

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include "cell.h"
#include "utils.h"

typedef struct node_l{
	cell *c;
	struct node_l *next;
} node_l;

typedef struct list{
	node_l *first;
} list;

/*
 * Creates and returns a new list.
 */
list *new_l();

/*
 * Pops and returns the first node of the list.
 */
cell *front_l(list *l);

/*
 * Appends a node at the front of the list.
 */
void append_front_l(list *l, cell *c);

/*
 * Deletes a cell, given the content.
 */
void delete_l(list *l, cell *c);

/*
 * Returns true iif the list contains a node with a given cell.
 */
bool contains_l(list *l, cell *c);

/*
 * Frees the content of each node.
 */
void free_cells_l(list *l);

/*
 * Frees the memory used by the list. Note that it does not free
 * cell's memory.
 */
void destroy_l(list *l);

/*
 * Prints the list.
 */
void print_l(list *l);

#endif
