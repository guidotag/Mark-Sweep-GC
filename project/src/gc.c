#include "../include/gc.h"

/*
 * free_list contains all the free cells, i. e., cells for which memory
 * has been allocated, but it isn't in use.
 */
list *free_list;

/*
 * live_list contains all the living cells, i. e., cells which hold
 * objects being used by the main program.
 */
list *live_list;

/*
 * root_list contains all the root cells.
 */
list *root_list;

void init_gc(uint initial_free_cells, uint object_size){
	free_list = new_l();
	live_list = new_l();
	root_list = new_l();
	
	int i;
	for(i = 0; i < initial_free_cells; i++){
		append_front_l(free_list, new_c(object_size));
	}
}

void terminate_gc(){
	free_cells_l(live_list);
	free_cells_l(free_list);
	destroy_l(free_list);
	destroy_l(live_list);
	destroy_l(root_list);
}

void *new(){
	cell *c = NULL;
	
	if(free_list->first == NULL){
		/* Maybe we find some free memory running the GC */
		DEFAULT_MARK_SWEEP();
	}
	
	if(free_list->first == NULL){
		/* No memory available */
		return NULL;
	}
	
	c = front_l(free_list);
	append_front_l(live_list, c);

	/* Returns the object's starting address */
	return get_object(c);
}

void sweep(){
	node_l **n = &(live_list->first);
	
	while(*n != NULL){
		cell *c = (*n)->c;

		if(c->mark_bit == 1){
			c->mark_bit = 0;
			n = &((*n)->next);
		}else{
			node_l *next = (*n)->next;
			free(*n);
			*n = next;
						
			append_front_l(free_list, c);
		}
	}
}

void mark_std(cell *c){
	if(c->mark_bit == 0){
		c->mark_bit = 1;
		uintptr_t addr = (uintptr_t)get_object(c);
		while(addr + sizeof(uintptr_t) <= (uintptr_t) c + sizeof(cell) + c->size){
			void *ptr = (void *) *((uintptr_t *) addr);
			if(is_pointer(ptr)){
				mark_std(get_header(ptr));
			}
			addr++;
		}
	}
}

void mark_fast(trie *t, cell *c){
	stack *s = new_s();
	
	push_s(s, c);
	
	while(!is_empty_s(s)){
		c = pop_s(s);
		if(c->mark_bit == 0){
			c->mark_bit = 1;
			uintptr_t addr = (uintptr_t)get_object(c);
			while(addr + sizeof(uintptr_t) <= (uintptr_t) c + sizeof(cell) + c->size){
				void *ptr = (void *) *((uintptr_t *) addr);
				if(get_id_t(t, ptr) >= MIN_ID){
					push_s(s, get_header(ptr));
				}
				addr++;
			}
		}
	}

	destroy_s(s);
}

void mark_sweep_std(){
	node_l *n = root_list->first;
	
	while(n != NULL){
		mark_std(n->c);
		n = n->next;
	}
	
	sweep();
}

void mark_sweep_fast(){
	trie *t = new_t();
	fill_live_trie(t);

	node_l *n = root_list->first;
	
	while(n != NULL){
		mark_fast(t, n->c);
		n = n->next;
	}
	
	sweep();
	
	destroy_t(t);
}

void set_root(void *object){
	cell *c = get_header(object);
	append_front_l(root_list, c);
}

void set_null(void **object){
	cell *c = get_header(*object);
	delete_l(root_list, c);
	
	uintptr_t *ptr = (uintptr_t *) object;
	*ptr = (uintptr_t) NULL;
}

bool is_pointer(void *object){
	cell *c = get_header(object);
	
	return contains_l(live_list, c);
}

void fill_live_trie(trie *t){
	node_l *n = live_list->first;
	int ids = MIN_ID;
	
	while(n != NULL){
		insert_t(t, get_object(n->c), ids++);
		n = n->next;
	}
}

void print_status(){
	print_sep('-');
	printf("Memory status:\n\n");
	printf("> Live list: \n");
	
	print_l(live_list);
	
	printf("> Root list:\n");

	print_l(root_list);
	print_sep('-');
}
