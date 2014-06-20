#include "../include/trie.h"

trie *new_t(){
	trie *t = (trie *) malloc(sizeof(trie));
	t->root = NULL;
	
	return t;
}

static void print_branch(node_t *n, char *addr, int depth){
	while(n != NULL){
		addr[depth] = n->c;
		
		if(n->id != -1){
			printf("0x%s (id: %i)\n", addr, n->id);
		}
		
		print_branch(n->down, addr, depth + 1);
		n = n->next;
	}
	
	addr[depth] = '\0';
}

static void destroy_branch(node_t *n){
	while(n != NULL){
		node_t *next = n->next;
		destroy_branch(n->down);
		free(n);
		n = next;
	}
}

void insert_t(trie *t, void *ptr, int id){
	assert(id >= MIN_ID);
		
	char *hexa = to_base((unsigned long long) ptr, 16, 0);
	int i = 0;
	node_t **n = &(t->root);
	
	while(hexa[i] != '\0'){
		bool found = FALSE;

		while(*n != NULL){
			if((*n)->c == hexa[i]){
				found = TRUE;
				break;
			}
			n = &((*n)->next);
		}
		
		if(!found){
			*n = (node_t *) malloc(sizeof(node_t));
			(*n)->c = hexa[i];
			(*n)->id = MIN_ID - 1;
			(*n)->next = NULL;
			(*n)->down = NULL;
		}
		
		if(hexa[i + 1] == '\0'){
			(*n)->id = id;
		}
		
		n = &((*n)->down);
		i++;
	}
	
	free(hexa);
}

int get_id_t(trie *t, void *ptr){
	char *hexa = to_base((unsigned long long) ptr, 16, 0);
	int i = 0;
	node_t **n = &(t->root);
	
	while(hexa[i] != '\0'){
		bool found = FALSE;

		while(*n != NULL){
			if((*n)->c == hexa[i]){
				found = TRUE;
				break;
			}
			n = &((*n)->next);
		}
		
		if(!found){
			free(hexa);
			return MIN_ID - 1;
		}
		
		if(hexa[i + 1] != '\0'){
			n = &((*n)->down);
		}
		
		i++;
	}
	
	free(hexa);
	
	return (*n)->id;
}

void print_t(trie *t){
	assert(t != NULL);
	
	if(t->root == NULL){
		printf("Empty trie\n");
	}else{
		char addr[MAX_ADDR_LENGTH + 1];
		memset(addr, '\0', MAX_ADDR_LENGTH + 1);
		
		print_branch(t->root, addr, 0);
	}
}

void destroy_t(trie *t){
	assert(t != NULL);
	destroy_branch(t->root);
	free(t);
}
