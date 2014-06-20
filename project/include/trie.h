/*
 * Dictionary data structure. Specifically a dictionary represented as a trie.
 * 
 * Author: Guido Tagliavini Ponce
 */

#ifndef __TRIE_H_INCLUDED__
#define __TRIE_H_INCLUDED__

#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "defines.h"

typedef struct node_t{
	int id;
	char c;
	struct node_t *down;
	struct node_t *next;
} node_t;

typedef struct trie{
	node_t *root;
} trie;

/*
 * Creates and returns a new dictionary.
 */
trie *new_t();

/*
 * Inserts the key given by the address in ptr, and associates it to the value id.
 */
void insert_t(trie *t, void *ptr, int id);

/*
 * Returns the key of the key ptr. Returns MIN_ID - 1 if the key was not found.
 */
int get_id_t(trie *t, void *ptr);

/*
 * Prints the dictionary.
 */
void print_t(trie *t);

/*
 * Destroys the dictionary.
 */
void destroy_t(trie *t);

#endif
