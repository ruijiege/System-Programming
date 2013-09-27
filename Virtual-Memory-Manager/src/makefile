main : main.o options.o optimal.o FIFO.o LFU.o LRU_CLOCK.o LRU_STACK.o LRU_REF8.o
	gcc main.o options.o optimal.o FIFO.o LFU.o LRU_CLOCK.o LRU_STACK.o LRU_REF8.o -o main
main.o : main.c main.h options.h optimal.h FIFO.h LFU.h LRU_CLOCK.h LRU_STACK.h LRU_REF8.h
	gcc -c  -Wall main.c
options.o : options.c options.h main.h
	gcc -c  -Wall options.c
optimal.o : optimal.c optimal.h main.h
	gcc -c -Wall  optimal.c
FIFO.o : FIFO.c FIFO.h main.h
	gcc -c -Wall FIFO.c
LFU.o : LFU.c LFU.h main.h
	gcc -c -Wall LFU.c
LRU_CLOCK.o : LRU_CLOCK.c LRU_CLOCK.h main.h
	gcc -c -Wall LRU_CLOCK.c
LRU_STACK.o : LRU_STACK.c LRU_STACK.h main.h
	gcc -c -Wall LRU_STACK.c
LRU_REF8.o : LRU_REF8.c LRU_REF8.h main.h
	gcc -c -Wall LRU_REF8.c
.PHONY : clean
clean :
	rm -f main.o options.o optimal.o FIFO.o LFU.o LRU_CLOCK.o LRU_STACK.o LRU_REF8.o
