#ifndef ALLOC_LL_HEADER
#define ALLOC_LL_HEADER

#include "linked_list.h"

#define SIZE_HEAP 1024

void* heap;

double_linked_list* buffer_tracker;

#define BUFF_FREE 'F'
#define BUFF_FILLED 'B'

void buffer_tracker_print(void);
void init_heap(void);
void free_heap(void);

// allocate a pointer of size size
void* heap_malloc(unsigned int size);
// free a pointer in the heap
void heap_free(void *ptr);
void defragmentation(double_linked_list* liste);

double_linked_list* (*strategy)(unsigned int size);
void set_strategy(double_linked_list* (*strat)(unsigned int size));
double_linked_list* first_fit(unsigned int size);

#endif