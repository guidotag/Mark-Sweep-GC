#include "../include/test_gc.h"

extern list *free_list;
extern list *live_list;
extern list *root_list;

/* Some objects we'll use for testing. */

typedef struct objectA{
	int a;
	int b;
} objectA;

typedef struct objectB{
	objectA *objA;
	int a;
} objectB;

typedef struct objectC{
	int a;
	int b;
	double c;
	int *d;
} objectC;

typedef struct objectD{
	objectA *objA;
	objectB *objB;
	char a;
	struct objectD *objD;
} objectD;

typedef struct objectE{
	struct objectE *objE;
} objectE;

typedef struct objectF{
	struct objectE *objE1;
	struct objectE *objE2;
} objectF;

void test_gc_new(){
	printf("\ntest_gc_new\n");
	
	init_gc(5 /*initial_free_cells*/, 32 /*object_size*/);
	objectC *objC = new();
	objC->a = 747;
	objC->b = 3;
	objC->c = 3.14;
	objC->d = (void *) 0x123456;
	set_root(objC);
	
	print_l(live_list);
	
	terminate_gc();
}

void test_gc_set_null(){
	printf("\ntest_gc_set_null\n");
	
	init_gc(5, 32);
	objectA *objA = new();
	objA->a = 123;
	objA->b = 6125;
	set_root(objA);
	
	print_l(live_list);
	
	set_null((void **) &objA);
	
	DEFAULT_MARK_SWEEP();
	
	print_l(live_list);
	
	terminate_gc();
}

void test_gc_mark_sweep_1(){
	printf("\ntest_gc_mark_sweep_1\n");
	
	init_gc(5, 32);
	
	/* First we allocate objA. */
	
	objectA *objA = new();
	objA->a = 123;
	objA->b = 6125;
	set_root(objA);
	
	print_l(live_list);
	
	/* Now we allocate objB, which references objA. */
	
	objectB *objB = new();
	objB->objA = objA;
	objB->a = 15123;
	set_root(objB);
	
	print_l(live_list);
	
	/* Setting objA to null, objA is no more a root object.
	 * Therefore objA is no more a living object, but since
	 * objB references objA, the GC should not free objA.
	 */
	
	set_null((void **) &objA);
	
	DEFAULT_MARK_SWEEP();
	
	print_l(live_list);
	
	/* We set objB to null. This causes both objA and
	 * objB to disappear.
	 */
	
	set_null((void **) &objB);
	
	DEFAULT_MARK_SWEEP();
	
	print_l(live_list);
	
	terminate_gc();
}

void test_gc_mark_sweep_2(){
	printf("\ntest_gc_mark_sweep_2\n");
	
	init_gc(5, 32);
	
	objectE *objE1 = new();
	set_root(objE1);
	
	objectE *objE2 = new();
	objE1->objE = objE2;
	
	objectE *objE3 = new();
	objE2->objE = objE3;
	
	objectE *objE4 = new();
	set_root(objE4);
	objE4->objE = objE2;
	
	/* We have the following references:
	 * E1 --> E2
	 * E2 --> E3
	 * E4 --> E2
	 * 
	 * where E1 and E4 are the only two roots.
	 */
	 
	 /* To have a clearer picture of what happens when running the GC,
	  * add a few print_t statements in the mark and sweep function */
	
	print_l(live_list);

	/* Running the GC doesn't have any effect. */
	
	DEFAULT_MARK_SWEEP();
	
	print_l(live_list);	
	
	set_null((void **) &objE1);
	
	/* The GC just frees E1, because every other object is
	 * reachable from E2. */
	
	DEFAULT_MARK_SWEEP();
	
	print_l(live_list);
	
	set_null((void **) &objE4);
	
	DEFAULT_MARK_SWEEP();
	
	/* Nullyfing objE4 means that no object is reachable, and thus
	 * the GC will free everything. */
	
	print_l(live_list);
	
	terminate_gc();
}

/* F  --> E1 --> E2
 * |      |      ʌ
 * v      v      |
 * E3 --> E4 --> E5
 * 
 * Roots: F, E4
 */
void test_gc_mark_sweep_3(){
	printf("\ntest_gc_mark_sweep_3\n");
	
	init_gc(10, 32);
	
	/* For this test we need the GC to have a bunch of memory pre-allocated,
	 * because we don't want it to mark and sweep before all the relations
	 * between objects are set.
	 */
	
	objectF *objF = new();
	set_root(objF);
	
	objectE *objE1 = new();
	objF->objE1 = objE1;
	
	objectE *objE2 = new();
	objE2->objE = objE1;
	
	objectE *objE3 = new();
	objF->objE2 = objE3;
	
	objectE *objE4 = new();
	set_root(objE4);
	objE1->objE = objE4;
	objE3->objE = objE4;
	
	objectE *objE5 = new();
	objE5->objE = objE2;
	objE4->objE = objE5;
	
	print_status();
	
	set_null((void **) &(objF));
	
	DEFAULT_MARK_SWEEP();
	
	print_status();
	
	set_null((void **) &(objE4));
	
	DEFAULT_MARK_SWEEP();
	
	print_status();
		
	terminate_gc();
}

void test_gc(){
	test_gc_new();
	test_gc_set_null();
	test_gc_mark_sweep_1();
	test_gc_mark_sweep_2();
	test_gc_mark_sweep_3();
}
