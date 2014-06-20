#include "../include/list.h"

list *new_l(){
	list *l = (list *) malloc(sizeof(list));
	l->first = NULL;
	return l;
}

cell *front_l(list *l){
	if(l->first == NULL){
		return NULL;
	}
	
	node_l *next = l->first->next;
	cell *c = l->first->c;
	free(l->first);
	l->first = next;
	
	return c;
}

void append_front_l(list *l, cell *c){
	node_l *n = (node_l *) malloc(sizeof(node_l));
	n->c = c;
	n->next = l->first;
	l->first = n;
}

void delete_l(list *l, cell *c){
	assert(l != NULL);
	
	node_l **n = &(l->first);
	
	while(*n != NULL){
		if((*n)->c == c){
			node_l *next = (*n)->next;
			free(*n);
			*n = next;		
			break;
		}
		n = &((*n)->next);
	}
}

bool contains_l(list *l, cell *c){
	assert(l != NULL);
	
	node_l *n = l->first;
	
	while(n != NULL){
		if(n->c == c){
			return TRUE;
		}
		n = n->next;
	}
	
	return FALSE;
}

void free_cells_l(list *l){
	assert(l != NULL);
	
	node_l *n = l->first;
	
	while(n != NULL){
		destroy_c(n->c);
		n = n->next;
	}
}

void destroy_l(list *l){
	assert(l != NULL);
	
	node_l *n = l->first;
	
	while(n != NULL){
		node_l *next = n->next;
		free(n);
		n = next;
	}
	
	free(l);
}

void print_l(list *l){
	assert(l != NULL);
		
	if(l->first == NULL){
		print_sep('-');	
		printf("Empty list\n");
	}else{
		node_l *n = l->first;
		
		while(n != NULL){
			print_sep('-');
			print_c(n->c);
			n = n->next;
		}
	}
	
	print_sep('-');
}
