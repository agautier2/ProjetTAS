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

	char* p1 = heap_malloc(10);
	/*print_heap();*/

	CU_ASSERT(p1 == (char*) buffer_tracker->ptr+10);
	CU_ASSERT(p1 == NULL);

	//CU_ASSERT(*(p1+1) != FREE_BLOCK);

	//CU_ASSERT(libre == 10+1);
	//CU_ASSERT(*(heap + libre) == 116);
	//CU_ASSERT(*(heap + libre + 1) == FREE_BLOCK);

	//char* p2 = heap_malloc(9);
	/*print_heap();*/

	//CU_ASSERT(get_index_on_heap(p2) == 12);
	//CU_ASSERT(get_block_size(p2) == 9);
	//CU_ASSERT(libre == 21);

	//char* p3 = heap_malloc(5);
	/*print_heap();*/

	//CU_ASSERT(get_index_on_heap(p3) == 22);
	//CU_ASSERT(get_block_size(p3) == 5);
	//CU_ASSERT(libre == 27);

	//char* p4 = heap_malloc(101);
	/*print_heap();*/

	//CU_ASSERT(p4 == NULL);
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