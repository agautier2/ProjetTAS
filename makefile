CC ?= gcc
CFLAGS += -Wall --pedantic -Werror
DEBUG_FLAGS += -g
LOCAL_LIB=/home/agautier/C/ProjetTAS/poei-linkedlist
LOCAL_INC=/home/agautier/C/ProjetTAS/poei-linkedlist

all:
	$(CC) $(LDFLAGS) -I$(LOCAL_INC) -L$(LOCAL_LIB) -o allocation $(CFLAGS) $(DEBUG_FLAGS) allocation.c main.c -llinkedlist
test_d_ll_debug:
	$(CC) $(LDFLAGS) -I$(LOCAL_INC) -L$(LOCAL_LIB) -o debug_test_allocation $(CFLAGS) $(DEBUG_FLAGS) test_allocation.c allocation.c $(CFILES) -lcunit -llinkedlist 
lib:
	cd poei-linkedlist && make lib
valgrind:
	make test && valgrind --leak-check=yes ./test_allocation
clean:
	rm -f *.o allocation test_allocation *.so *.a
