#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ds_memory.h"


struct ds_file_struct ds_file; /*Global variable that holds file pointer and block arrays*/
struct ds_counts_struct ds_counts; /*Global variable that reads and write counts*/


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

    return (0); /*Program closes*/
}

/*
* int ds_create creates a giant block in the file that has
* no memory allocation in any size
*/
int ds_create (char *filename, long size) {

	return (0);
	
}

int ds_init (char *filename) {
	
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

