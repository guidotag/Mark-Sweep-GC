/*
 * Stack data structure.
 * 
 * Author: Guido Tagliavini Ponce
 */

#ifndef __STACK_H__
#define __STACK_H__

#include "list.h"

typedef struct stack{
	list *l;
} stack;

stack *new_s();

void push_s(stack *s, cell *c);

cell *pop_s(stack *s);

bool is_empty_s(stack *s);

void destroy_s(stack *s);

#endif
