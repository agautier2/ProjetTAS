#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "allocation.h"
#include "linked_list.h"


void test_heap_init(){
	init_heap();

	CU_ASSERT(buffer_tracker->size == SIZE_HEAP);
	CU_ASSERT(buffer_tracker->filled == BUFF_FREE);
}


void test_heap_malloc_example(){

	init_heap();
	double_linked_list* pointeur = buffer_tracker;
    buffer_tracker_print();
	char* p1 = heap_malloc(10);
	buffer_tracker_print();
	char* p2 = heap_malloc(15);
	buffer_tracker_print();
	/*print_heap();*/

	CU_ASSERT(p1 == (char*) heap);
	CU_ASSERT(p1 == (char*) pointeur->ptr);
	CU_ASSERT(pointeur->size == 10);
	CU_ASSERT(pointeur->filled==BUFF_FILLED);
	pointeur=pointeur->next;
	CU_ASSERT(p2 == (char*) pointeur->ptr);
	CU_ASSERT(p2 == (char*) heap+10);
	CU_ASSERT(pointeur->size == 15);
	CU_ASSERT(pointeur->filled==BUFF_FILLED);
	pointeur=pointeur->next;
	CU_ASSERT(pointeur->filled==BUFF_FREE);
	CU_ASSERT(pointeur->size==SIZE_HEAP-10-15);
	CU_ASSERT(pointeur->ptr==(char*)heap+10+15);
	
}


int init_suite(void) { return 0; }
int clean_suite(void) { return 0; }

int main()
{
	CU_pSuite pSuite = NULL;

	/* initialize the CUnit test registry */
	if (CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();

	/* add a suite to the registry */
	pSuite = CU_add_suite("Suite_1", init_suite, clean_suite);
	if (NULL == pSuite) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* add the tests to the suite */
	if (
		NULL == CU_add_test(pSuite, "test_heap_init()", test_heap_init)||
		NULL == CU_add_test(pSuite, "test_heap_malloc_example()", test_heap_malloc_example)
		
	)
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* Run all tests using the CUnit Basic interface */
	CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();
}