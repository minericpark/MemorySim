/*  Eric Minseo Park 
    1001018
    epark03@uoguelph.ca   */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_BLOCKS 4096

struct ds_counts_structs;
struct ds_blocks_structs;
struct ds_file_structs;

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