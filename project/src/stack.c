#include "../include/stack.h"

stack *new_s(){
	stack *s = (stack *) malloc(sizeof(stack));
	s->l = new_l();
	
	return s;
}

void push_s(stack *s, cell *c){
	append_front_l(s->l, c);
}

cell *pop_s(stack *s){
	cell *c = front_l(s->l);
	return c;
}

bool is_empty_s(stack *s){
	return s->l->first == NULL;
}

void destroy_s(stack *s){
	destroy_l(s->l);
	free(s);
}

