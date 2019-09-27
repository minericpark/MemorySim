CC=gcc
CFLAGS=-Wall -ansi -Iincludes
DEP = ds_memory.h
	
all: ds_memory ds_array ds_list

ds_memory: ds_memory.c
	$(CC) $(CFLAGS) ds_memory.c -o ds_memory

ds_memory-debug:
	$(CC) $(CFLAGS) -D DEBUG ds_memory.c -o ds_memory-debug
	
ds_array: ds_array.c
	$(CC) $(CFLAGS) ds_memory.c ds_array.c -o ds_array
	
ds_list: ds_list.c
	$(CC) $(CFLAGS) ds_memory.c ds_list.c -o ds_list

clean:
	rm ds_memory.o ds_array.o