CC ?= gcc
CFLAGS += -Wall --pedantic -Werror
DEBUG_FLAGS += -g
LOCAL_LIB=/home/agautier/C/ProjetTAS/poei-linkedlist
LOCAL_INC=/home/agautier/C/ProjetTAS/poei-linkedlist

all:
	$(CC) $(LDFLAGS) -I$(LOCAL_INC) -L$(LOCAL_LIB) -o allocation $(CFLAGS) $(DEBUG_FLAGS) allocation.c main.c -llinkedlist
test_d_ll_debug:
	$(CC) $(LDFLAGS) -I$(LOCAL_INC) -L$(LOCAL_LIB) -o debug_d_ll_allocation_tests $(CFLAGS) $(DEBUG_FLAGS) tests/test_d_ll_allocation.c $(CFILES) -lcunit
lib:
	cd poei-linkedlist && make lib
valgrind:
	make test && valgrind --leak-check=yes ./test_allocation
clean:
	rm -f *.o allocation test_allocation *.so *.a
