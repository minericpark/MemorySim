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

	/*#ifdef DEBUG
		int i = 0;
		int size = 1234;
		
		
		printf ("Debugging is turned on\n");
		printf ("sizeof(struct ds_counts_struct) = %ld\n", sizeof(struct ds_counts_struct));
		printf ("sizeof(struct ds_blocks_struct) = %ld\n", sizeof(struct ds_blocks_struct));
		printf ("sizeof(struct ds_file_struct) = %ld\n", sizeof(struct ds_file_struct));
	
		ds_create ("test", size); 
		
		printf ("%s\n", ds_file.fp); 
		ds_init ("test");
		
		printf ("Searching for block of size 1234\n");
		printf ("Return value is %ld\n", ds_malloc (10));
		printf ("Searching for block of large size\n");
		printf ("Return value is %ld\n", ds_malloc(100000));
		
		ds_free(0);
		
		printf ("Block Num	Start	Length	Alloced\n");
		for (i = 0; i < MAX_BLOCKS; i++) {
			printf ("%d		%ld	%ld 	%d\n", i, ds_file.block[i].start, ds_file.block[i].length, ds_file.block[i].alloced);
		}
		printf ("Read = %d, Write = %d\n", ds_counts.reads, ds_counts.writes);
		
		
		ds_finish();
		
		
		
	#endif */
	
	long memory;

	int i;
	int size = 1234;

	ds_create("test.bin", size);

	ds_init( "test.bin");

	printf( "Calling ds_malloc( 10 )\n");
	memory = ds_malloc( 10);
	printf( "Return value is %ld\n", memory );
	
	printf( "Calling ds_malloc( 100000 )\n");
	printf( "Return value is %ld\n", ds_malloc( 100000) );
	
	printf( "Calling ds_malloc( 17 )\n");
	printf( "Return value is %ld\n", ds_malloc( 17) );

	ds_free( memory );

	ds_finish();
	
	
	printf ("Block Num	Start	Length	Alloced\n");
	for (i = 0; i < MAX_BLOCKS; i++) {
		printf ("%d		%ld	%ld 	%d\n", i, ds_file.block[i].start, ds_file.block[i].length, ds_file.block[i].alloced);
	}
	printf ("Read = %d, Write = %d\n", ds_counts.reads, ds_counts.writes);
		
	
    return (0); /*Program closes*/
}

/*
* int ds_create creates a giant block in the file that has
* no memory allocation in any size
*/
int ds_create (char *filename, long size) {

	int i;
	char *zero = 0;
	
	if ((ds_file.fp = fopen (filename, "wb+")) == NULL) { /*File checker*/
		printf ("Error: file could not be opened\n");
		return -1;
	}	
	
	if (fseek (ds_file.fp, 0, SEEK_SET) != 0) {
		printf ("Error: file pointer was not reset\n");
		return -1;
	}

	for (i = 0; i < MAX_BLOCKS; i++) {
		ds_file.block[i].start = 0;
		ds_file.block[i].length = 0;
		ds_file.block[i].alloced = 0;
	}
	ds_file.block[0].length = size;
	for (i = 0; i < MAX_BLOCKS; i++) {
		if (fwrite (&ds_file.block[i], sizeof (struct ds_blocks_struct), 1, ds_file.fp) != 1) {
			printf ("Error: file could not be written into\n");
			return -1;
		}
	}
	if (fwrite (&zero, sizeof (char) * size, 1, ds_file.fp) != 1) {
		printf ("Error: file could not be written into\n");
		return -1;
	}
	if (fclose (ds_file.fp) == EOF) {
		printf ("Error: file could not be closed\n");
		return -1;
	}
	
	return (0);
	
}

int ds_init (char *filename) {
	
	if ((ds_file.fp = fopen (filename, "rb+")) == NULL) {
		printf ("Error: file could not be opened\n");
		return -1;
	}
	if (fread (&ds_file.block, sizeof(ds_file.block), 1, ds_file.fp) != 1) {
		printf ("Error: file could not be read\n");
		return -1;
	}
	ds_counts.reads = 0;
	ds_counts.writes = 0;
	if (fclose (ds_file.fp) == EOF) {
		printf ("Error: file could not be closed\n");
		return -1;
	}
	return (0);
	
}

long ds_malloc (long amount) {
	
	int i;
	long tempStart;
	long tempLength;
	int secondBlockFound = 0;
	
	for (i = 0; i < MAX_BLOCKS; i++) {
		if (ds_file.block[i].length >= amount && ds_file.block[i].alloced == 0) {
			tempStart = ds_file.block[i].start;
			tempLength = ds_file.block[i].length;
			ds_file.block[i].length = amount;
			ds_file.block[i].alloced = 1;
			for (i = 0; i < MAX_BLOCKS; i++) {
				if (ds_file.block[i].length == 0 && secondBlockFound == 0) {
					secondBlockFound = 1;
					ds_file.block[i].start = tempStart + amount;
					ds_file.block[i].length = tempLength - amount;
					ds_file.block[i].alloced = 0;
				}
			}
			return ds_file.block[i].start;
		}			
	}	
	return (-1);
	
}

void ds_free (long start) {
	
	int i;
	
	for (i = 0; i < MAX_BLOCKS; i++) {
		if (ds_file.block[i].start == start) {
			ds_file.block[i].alloced = 0;
		}
	}
	
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
	
	int i;
	
	if (fseek (ds_file.fp, 0, SEEK_SET) != 0) {
		return -1;
	}
	/*Error check when file reads in*/
	/*fwrite (&ds_file, sizeof(ds_file), 0, ds_file.fp);*/
	for (i = 0; i < MAX_BLOCKS; i++) {
		if (fwrite (&ds_file.block[i], sizeof (struct ds_blocks_struct), 1, ds_file.fp) != 1) {
			printf ("Error: file could not be written into\n");
			return -1;
		}
	}
	fclose (ds_file.fp);
	return (0);
	
}

