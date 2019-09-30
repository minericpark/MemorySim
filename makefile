CC=gcc
CFLAGS=-Wall -ansi -pedantic -Iincludes 
DEP = ds_memory.h
	
all: ds_memory ds_array ds_list

ds_memory: ds_memory.c
	$(CC) $(CFLAGS) -c ds_memory.c -o ds_memory.o

ds_memory-debug:
	$(CC) $(CFLAGS) -D DEBUG ds_memory.c -o ds_memory-debug

ds_array: ds_array.c ds_array.h ds_memory.h
	$(CC) $(CFLAGS) -c ds_array.c -o ds_array.o

ds_list: ds_list.c ds_list.h ds_memory.h
	$(CC) $(CFLAGS) -c ds_list.c -o ds_list.o
	
analysisProgram: analysisProgram.c ds_array.h ds_memory.h
	$(CC) $(CFLAGS) -c analysisProgram.c -o analysisProgram.o

clean:
	rm ds_memory.o ds_array.o ds_list.o