#include <stdio.h>
#include "../include/test_gc.h"
#include "../include/test_list.h"
#include "../include/test_trie.h"

int main(){	
	test_gc();
	test_trie();
	test_list();
	
	return 0;
}
