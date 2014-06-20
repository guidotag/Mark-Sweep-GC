/*
 * gc.h functions tests.
 */

#ifndef __TEST_GC_H__
#define __TEST_GC_H__

#include <stdlib.h>
#include "../../include/gc.h"
#include "../../include/utils.h"
#include "../../include/defines.h"

void test_gc_new();

void test_gc_set_null();

void test_gc_mark_sweep_1();
	
void test_gc_mark_sweep_2();

void test_gc_mark_sweep_3();

void test_gc();

#endif

