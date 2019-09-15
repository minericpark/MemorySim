#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ds_memory.h"

struct ds_file_struct ds_file;
struct ds_counts_struct ds_counts;

struct ds_counts_struct {
	int reads;
	int writes;
}

struct ds_blocks_struct {
	long start;
	long length;
	char alloced;
}

struct ds_file_struct {
	FILE *fp;
	struct ds_blocks_struct block[MAX_BLOCKS];
}

int main () {

    return (0); //Program closes
}

int ds_create (char *filename, long size) {
	
}

int ds_init (char *filename) {
	
}

long ds_malloc (long amount) {
	
}

void ds_free (long start) {
	
}

void *ds_read (void *ptr, long start, long bytes) {
	
}

long ds_write (long start, void *ptr, long bytes) {
	
}

int ds_finish () {
	
}

