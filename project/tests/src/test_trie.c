#include "../include/test_trie.h"

void test_trie_insert(){
	printf("\ntest_trie_insert\n");
	
	trie *t = new_t();
	
	/* Insert a few pointers and print the trie.
	 * We test the trie, inserting pointers which have common prefixes,
	 * for example 0x654321 and 0x6543, 0x123456 and 0x1236.
	 */
	
	uintptr_t ptr = 0x123456;
	insert_t(t, (void *) ptr, 0);
	
	ptr = 0x654321;
	insert_t(t, (void *) ptr, 1);
	
	ptr = 0x1236;
	insert_t(t, (void *) ptr, 2);
	
	ptr = 0x6543;
	insert_t(t, (void *) ptr, 3);
	
	print_t(t);

	destroy_t(t);
}

void test_trie_get_id(){
	printf("\ntest_trie_get_id\n");
	
	trie *t = new_t();
	
	/* Insert a few pointers. */
	
	uintptr_t ptr = 0x123456;
	insert_t(t, (void *) ptr, 0);

	ptr = 0x654321;
	insert_t(t, (void *) ptr, 1);
	
	ptr = 0x1236;
	insert_t(t, (void *) ptr, 2);
	
	ptr = 0x6543;
	insert_t(t, (void *) ptr, 3);
	
	/*
	 * Now we test for key containment and value.
	 */
	
	ptr = 0x123456;
	assert(get_id_t(t, (void *) ptr) == 0);
	
	ptr = 0x12312;
	assert(get_id_t(t, (void *) ptr) < MIN_ID);
	
	ptr = 0x12345;
	assert(get_id_t(t, (void *) ptr) < MIN_ID);
	
	ptr = 0x1234567;
	assert(get_id_t(t, (void *) ptr) < MIN_ID);
	
	ptr = 0x1236;
	assert(get_id_t(t, (void *) ptr) == 2);
	
	ptr = 0x6543;
	assert(get_id_t(t, (void *) ptr) == 3);
	
	ptr = 0x65432;
	assert(get_id_t(t, (void *) ptr) < MIN_ID);
	
	ptr = 0x654321;
	assert(get_id_t(t, (void *) ptr) == 1);
	
	destroy_t(t);
}

void test_trie(){
	test_trie_insert();
	test_trie_get_id();
}
