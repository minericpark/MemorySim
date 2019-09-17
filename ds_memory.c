#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ds_memory.h"
/*#define DEBUG	1*/

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

	/*#ifdef DEBUG*/
		int i = 0;
		char buffer[ds_file.block->length];
		
		printf ("Debugging is turned on\n");
		printf ("sizeof(struct ds_counts_struct) = %ld\n", sizeof(struct ds_counts_struct));
		printf ("sizeof(struct ds_blocks_struct) = %ld\n", sizeof(struct ds_blocks_struct));
		printf ("sizeof(struct ds_file_struct) = %ld\n", sizeof(struct ds_file_struct));
	
		ds_create ("test", 10); /*Testing*/
		printf ("%s\n", ds_file.fp); /*Testing*/
		ds_init ("test"); /*Testing*/
		printf ("%d\n", ds_counts.reads); /*Testing*/
		printf ("%d\n", ds_counts.writes); /*Testing*/
		printf ("%ld\n", ds_file.block[0].start); /*Testing*/
		printf ("%ld\n", ds_file.block[0].length); /*Testing*/
		printf ("%c\n", ds_file.block[0].alloced); /*Testing*/

		printf ("%ld\n", ds_file.block[1].start); /*Testing*/
		printf ("%ld\n", ds_file.block[1].length); /*Testing*/
		printf ("%c\n", ds_file.block[1].alloced); /*Testing*/

		for (i = 0; i < ds_file.block->length; i++) { /*Testing*/
			fread (buffer, 1, ds_file.block->length, ds_file.fp);
			printf ("Block %d: %s\n", i + 1, buffer);
		}	
	/*#endif*/
	
    return (0); /*Program closes*/
}

/*
* int ds_create creates a giant block in the file that has
* no memory allocation in any size
*/
int ds_create (char *filename, long size) {

	int i;
	
	if ((ds_file.fp = fopen (filename, "wb")) == NULL) { /*File checker*/
		printf ("Error: file could not be opened\n");
		exit (-1);
	}	
	fseek (ds_file.fp, 0, SEEK_SET);
	for (i = 0; i < MAX_BLOCKS; i++) {
		ds_file.block[i].start = 0;
		ds_file.block[i].length = 0;
		ds_file.block[i].alloced = '0';
	}
	ds_file.block[0].length = size;
	for (i = 0; i < MAX_BLOCKS; i++) {
		fwrite (&ds_file.block[i], sizeof (struct ds_blocks_struct), i, ds_file.fp);
	}
	fseek (ds_file.fp, 0, SEEK_END);
	for (i = 0; i < size; i++) {
		fputs ("0", ds_file.fp);
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

