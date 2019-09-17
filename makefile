CC=gcc
CFLAGS=-Wall -ansi -I`
DEP = ds_memory.h
	
all: ds_memory.o ds_memory-debug
	
ds_memory.o: ds_memory.c $(DEP)
	$(CC) $(CFLAGS) -c ds_memory.c -o ds_memory.o

ds_memory: ds_memory.o
	$(CC) $(CFLAGS) ds_memory.o -o ds_memory

ds_memory-debug: ds_memory.o
	$(CC) $(CFLAGS) -D DEBUG ds_memory.o -o ds_memory

clean:
	rm ds_memory.o