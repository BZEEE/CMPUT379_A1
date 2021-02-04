
# Makefile for assignment 1

ifneq ($(USER_PAGE_SIZE),)
CFLAGS=-DUSER_PAGE_SIZE=$(USER_PAGE_SIZE)
else
CFLAGS=-DUSER_PAGE_SIZE=4096 # if argument wasnt provided set default page size to 4096 bytes
endif

all: mem_1.o mem_2.o mem_3.o get_mem_layout.o FORCE
	gcc $(CFLAGS) -Wall -std=c99 mem_1.o get_mem_layout.o -m32 -o mem_1.exe
	gcc $(CFLAGS) -Wall -std=c99 mem_2.o get_mem_layout.o -m32 -o mem_2.exe
	gcc $(CFLAGS) -Wall -std=c99 mem_3.o get_mem_layout.o -m32 -lm -o mem_3.exe

mem_1: mem_1.o get_mem_layout.o FORCE
	gcc $(CFLAGS) -Wall -std=c99 mem_1.o get_mem_layout.o -m32 -o mem_1.exe

mem_2: mem_2.o get_mem_layout.o FORCE
	gcc $(CFLAGS) -Wall -std=c99 mem_2.o get_mem_layout.o -m32 -o mem_2.exe

mem_3: mem_3.o get_mem_layout.o FORCE
	gcc $(CFLAGS) -Wall -std=c99 mem_3.o get_mem_layout.o -m32 -lm -o mem_3.exe

mem_1.o: mem_1.c mem_1.h FORCE
	gcc $(CFLAGS) -Wall -std=c99 -m32 -c mem_1.c

mem_2.o: mem_2.c mem_2.h FORCE
	gcc $(CFLAGS) -Wall -std=c99 -m32 -c mem_2.c

mem_3.o: mem_3.c mem_3.h FORCE
	gcc $(CFLAGS) -Wall -std=c99 -m32 -c -lm mem_3.c

get_mem_layout.o: get_mem_layout.c get_mem_layout.h FORCE
	gcc $(CFLAGS) -Wall -std=c99 -m32 -c get_mem_layout.c

.PHONY: clean
clean:
	rm -f *.out *.o *.exe

#force a rebuild for all targets 
FORCE:
