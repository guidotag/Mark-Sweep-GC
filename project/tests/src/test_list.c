#include "../include/test_list.h"

void test_list_append_front(){
	printf("\ntest_list_append_front\n");
	list *l = new_l();
	cell *c1 = new_c(8);
	cell *c2 = new_c(8);
	cell *c3 = new_c(8);
	
	append_front_l(l, c1);
	append_front_l(l, c2);
	append_front_l(l, c3);
	
	print_l(l);
	
	destroy_c(c1);	
	destroy_c(c2);
	destroy_c(c3);
	destroy_l(l);
}

void test_list_delete(){
	printf("\ntest_list_delete\n");
	
	list *l = new_l();
	cell *c1 = new_c(8);
	cell *c2 = new_c(8);
	cell *c3 = new_c(8);
	
	append_front_l(l, c1);
	append_front_l(l, c2);
	append_front_l(l, c3);
	
	print_l(l);
	
	delete_l(l, c2);
	
	print_l(l);
	
	delete_l(l, c3);
	
	print_l(l);
	
	delete_l(l, c1);
	
	print_l(l);
	
	append_front_l(l, c2);
	
	print_l(l);
	
	destroy_c(c1);	
	destroy_c(c2);
	destroy_c(c3);
	destroy_l(l);
}

void test_list_contains(){
	printf("\ntest_list_contains\n");
	list *l = new_l();
	cell *c1 = new_c(8);
	cell *c2 = new_c(8);
	cell *c3 = new_c(8);
	cell *c4 = new_c(8);
	
	append_front_l(l, c1);
	append_front_l(l, c2);
	append_front_l(l, c3);
	
	assert(contains_l(l, c1));
	assert(!contains_l(l, c4));
	assert(contains_l(l, c2));
	
	delete_l(l, c2);
	
	assert(!contains_l(l, c2));
	
	append_front_l(l, c4);
	
	assert(contains_l(l, c4));
	
	destroy_c(c1);	
	destroy_c(c2);
	destroy_c(c3);
	destroy_c(c4);
	destroy_l(l);
}

void test_list(){
	test_list_append_front();
	test_list_delete();
	test_list_contains();
}
