#include "../include/cell.h"

cell *new_c(uint size){
	cell *c = (cell *) malloc(sizeof(cell) + size);
	
	if(c != NULL){
		c->mark_bit = 0;
		c->size = size;
	}
	
	return c;
}

cell *get_header(void *object){
	return (cell *)((uintptr_t) object - sizeof(cell));
}

void *get_object(cell *c){
	return (void *)((uintptr_t) c + sizeof(cell));
}

void print_c(cell *c){
	printf("HEADER (at %p)\n", (void *) c);
	printf("\tMark bit: %i\n", c->mark_bit);
	printf("\tSize: %iB\n", c->size);
	
	uintptr_t *ptr = (uintptr_t *)get_object(c);
	printf("OBJECT (at %p)\n", (void *) ptr);
	while((uintptr_t) ptr < (uintptr_t) c + sizeof(cell) + c->size){
		printf("\t%p: %p\n", (void *)ptr, (void *) *ptr);
		ptr++;
	}
}

void destroy_c(cell *c){
	free(c);
}
