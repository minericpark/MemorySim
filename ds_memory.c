#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ds_memory.h"


struct ds_file_struct ds_file; /*Global variable that holds file pointer and block arrays*/
struct ds_counts_struct ds_counts; /*Global variable that reads and write counts*/

/*All function declarations*/
int ds_create (char *filename, long size);
int ds_init (char *filename);
long ds_malloc (long amount);
void ds_free (long start);
void *ds_read (void *ptr, long start, long bytes);
long ds_write (long start, void *ptr, long bytes);
int ds_finish ();

/*
* struct ds_counts_struct counts
* number of read and write operations
* performed
*/
struct ds_counts_struct {
	int reads;
	int writes;
};

/*
* struct ds_blocks_struct keeps track of
* blocks in the binary file
*/
struct ds_blocks_struct {
	long start;
	long length;
	char alloced;
};

/*
* struct ds_file_struct holds file pointer,
* opens it in binary in either read/write mode,
* and holds an array of blocks
*/
struct ds_file_struct {
	FILE *fp;
	struct ds_blocks_struct block[MAX_BLOCKS];
};

int main () {
	
	
	ds_create ("test", 10); /*Testing*/
	printf ("%s\n", ds_file.fp); /*Testing*/
	ds_init ("test"); /*Testing*/
	printf ("%d\n", ds_counts.reads); /*Testing*/
	printf ("%d\n", ds_counts.writes); /*Testing*/
	printf ("%d\n", ds_file.block->start);
	printf ("%d\n", ds_file.block->length);
	printf ("%c\n", ds_file.block->alloced);
    return (0); /*Program closes*/
}

/*
* int ds_create creates a giant block in the file that has
* no memory allocation in any size
*/
int ds_create (char *filename, long size) {

	ds_file.fp = fopen (filename, "wb"); /*File is created with filename in write binary mode*/
	fwrite (size, sizeof (size), 1, ds_file.fp);
	ds_file.block->start = 0;
	ds_file.block->length = size;
	ds_file.block->alloced = '0';
	if (ds_file.fp == NULL) { /*File checker*/
		printf ("Error: file could not be opened\n");
		exit (-1);
	}	
	fclose (ds_file.fp);
	return (0);
	
}

int ds_init (char *filename) {
	
	ds_file.fp = fopen (filename, "rb+");
	ds_counts.reads = 0;
	ds_counts.writes = 0;
	return (0);
	
}

long ds_malloc (long amount) {
	
	return (0);
	
}

void ds_free (long start) {
	
}

void *ds_read (void *ptr, long start, long bytes) {

	return ptr;

}

long ds_write (long start, void *ptr, long bytes) {
	
	return (0);
	
}

int ds_finish () {
	
	return (0);
	
}

