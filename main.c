#include <stdio.h>
#include "allocation.h"

int main(){
    init_heap();
    heap_malloc(10);
    return 0;
}