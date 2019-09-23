#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ds_memory.h"
#define DEBUG	1

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

int main () {

	#ifdef DEBUG
		int i = 0;
		char buffer[ds_file.block->length];
		int size = 1234;
		
		printf ("Debugging is turned on\n");
		printf ("sizeof(struct ds_counts_struct) = %ld\n", sizeof(struct ds_counts_struct));
		printf ("sizeof(struct ds_blocks_struct) = %ld\n", sizeof(struct ds_blocks_struct));
		printf ("sizeof(struct ds_file_struct) = %ld\n", sizeof(struct ds_file_struct));
	
		ds_create ("test", size); /*Testing*/
		printf ("%s\n", ds_file.fp); /*Testing*/
		ds_init ("test"); /*Testing*/

		printf ("Block Num	Start	Lenght	Alloced\n");
		for (i = 0; i < MAX_BLOCKS; i++) {
			printf ("%d		%ld	%ld 	%d\n", i, ds_file.block[i].start, ds_file.block[i].length, ds_file.block[i].alloced);
		}
		printf ("Read = %d, Write = %d", ds_counts.reads, ds_counts.writes);
	#endif
	
    return (0); /*Program closes*/
}

/*
* int ds_create creates a giant block in the file that has
* no memory allocation in any size
*/
int ds_create (char *filename, long size) {

	int i;
	char *zero = 0;
	
	if ((ds_file.fp = fopen (filename, "wb")) == NULL) { /*File checker*/
		printf ("Error: file could not be opened\n");
		return (1);
	}	
	fseek (ds_file.fp, 0, SEEK_SET);
	for (i = 0; i < MAX_BLOCKS; i++) {
		ds_file.block[i].start = 0;
		ds_file.block[i].length = 0;
		ds_file.block[i].alloced = 0;
	}
	ds_file.block[0].length = size;
	/*Error check when file writes in?*/
	for (i = 0; i < MAX_BLOCKS; i++) {
		fwrite (&ds_file.block[i], sizeof (struct ds_blocks_struct), 1, ds_file.fp);
	}
	fwrite (&zero, sizeof (char) * size, 1, ds_file.fp);
	/*Don't use for loop, write entire thing for sizeof entire array*/
	if (fclose (ds_file.fp) == EOF) {
		printf ("Error: file could not be closed\n");
		return (1);
	}
	
	return (0);
	
}

int ds_init (char *filename) {
	
	if ((ds_file.fp = fopen (filename, "rb+")) == NULL) {
		printf ("Error: file could not be opened\n");
	}
	fread (&ds_file, sizeof(ds_file), 0, ds_file.fp);
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

	ds_counts.reads++;
	return ptr;

}

long ds_write (long start, void *ptr, long bytes) {
	
	/*fseek (ds_file.fp, , start);*/
	ds_counts.writes++;
	return (0);
	
}

int ds_finish () {
	
	return (0);
	
}

