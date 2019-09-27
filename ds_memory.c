#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ds_memory.h"
/*#define DEBUG*/
/*#define TEST2*/

struct ds_file_struct ds_file; /*Global variable that holds file pointer and block arrays*/
struct ds_counts_struct ds_counts; /*Global variable that reads and write counts*/

/*
int main () {

	#ifdef DEBUG
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
		
		ds_test_init();
		
		
		ds_finish();
		
		
	#endif
	
	#ifdef TEST
		unsigned char c1, c2;
		unsigned short s1, s2;
		unsigned int i1, i2;
		unsigned long l1, l2;
		float f1,f2;
		double d1, d2;

		long memory[12];     
 
		int i;

		c1 = 0;
		c2 = 1;
		s1 = 20;
		s2 = 30;
		i1 = 40;
		i2 = 50;
		l1 = 60;
		l2 = 70;
		f1 = 80.0;
		f2 = 90.0;
		d1 = 100.0;
		d2 = 120.0;


		ds_create( "test.bin", 1234);

		ds_init( "test.bin");

		memory[0] = ds_malloc( sizeof(c1) );
		ds_write( memory[0], &c1, sizeof(c1) );

		memory[1] = ds_malloc( sizeof(c2) );
		ds_write( memory[1], &c2, sizeof(c2) );

		ds_free( memory[1] ); 

		memory[2] = ds_malloc( sizeof(s1) );
		ds_write( memory[2], &s1, sizeof(s1) );

		memory[3] = ds_malloc( sizeof(s2) );
		ds_write( memory[3], &s2, sizeof(s2) );

		ds_free( memory[3] ); 

		memory[4] = ds_malloc( sizeof(i1) );
		ds_write( memory[4], &i1, sizeof(i1) );

		memory[5] = ds_malloc( sizeof(i2) );
		ds_write( memory[5], &i2, sizeof(i2) );

		ds_free( memory[5] );

		memory[6] = ds_malloc( sizeof(l1) );
		ds_write( memory[6], &l1, sizeof(l1) );

		memory[7] = ds_malloc( sizeof(l2) );
		ds_write( memory[7], &l2, sizeof(l2) );

		ds_free( memory[7] );

		memory[8] = ds_malloc( sizeof(f1) );
		ds_write( memory[8], &f1, sizeof(f1) );

		memory[9] = ds_malloc( sizeof(f2) );
		ds_write( memory[9], &f2, sizeof(f2) );
 
		ds_free( memory[9] );

		memory[10] = ds_malloc( sizeof(d1) );
		ds_write( memory[10], &d1, sizeof(d1) );

		memory[11] = ds_malloc( sizeof(d2) );
		ds_write( memory[11], &d2, sizeof(d2) );

		ds_free( memory[11] );

		printf( "Remaining memory allocations:\n");
		for(i=0;i<12;i+=2) 
		{
			printf( "%ld\n", memory[i] );
		}


		ds_test_init();
		ds_finish();
	#endif
	
	#ifdef TEST2
	
		unsigned char c1;
	    unsigned short s1;
		unsigned int i1;
		unsigned long l1;
		float f1;
		double d1;

		long memory[6] = { 0, 2, 6, 14, 10, 30};
		ds_init( "test.bin");

		ds_read( &c1, memory[0],sizeof( c1 ) );
		ds_read( &s1, memory[1],sizeof( s1 ) );
		ds_read( &i1, memory[2],sizeof( i1 ) );
		ds_read( &l1, memory[3], sizeof( l1 ) );
		ds_read( &f1, memory[4],sizeof( f1 ) );
		ds_read( &d1, memory[5],sizeof( d1 ) );

		printf( "%d %d %d %ld %f %f\n", c1, s1, i1, l1, f1, d1 );
		ds_finish();
	
	#endif
	
    return (0); 
}
*/

void ds_test_init() {
	
	int i;
	
	printf ("Block Num	Start	Length	Alloced\n");
	for (i = 0; i < MAX_BLOCKS; i++) {
		printf ("%d		%ld	%ld 	%d\n", i, ds_file.block[i].start, ds_file.block[i].length, ds_file.block[i].alloced);
	}

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
			printf ("Error: file could not be written into or nothing to write!\n");
			return -1;
		}
	}
	if (fwrite (&zero, sizeof (char) * size, 1, ds_file.fp) != 1) {
		printf ("Error: file could not be written into or nothing to write!\n");
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
		printf ("Error: file could not be read or is empty\n");
		return -1;
	}
	ds_counts.reads = 0;
	ds_counts.writes = 0;
	return (0);
	
}

long ds_malloc (long amount) {
	
	int i;
	long tempStart;
	long tempLength;
	int secondBlockFound = 0;
	
	for (i = 0; i < MAX_BLOCKS; i++) {
		if (ds_file.block[i].length >= amount && ds_file.block[i].alloced == 0) {
			#ifdef DEBUG
			
				printf ("Discovered block %d, allocating...\n", i);
			
			#endif
			tempStart = ds_file.block[i].start;
			tempLength = ds_file.block[i].length;
			ds_file.block[i].length = amount;
			ds_file.block[i].alloced = 1;
			for (i = 0; i < MAX_BLOCKS; i++) {
				if (ds_file.block[i].length == 0 && secondBlockFound == 0) {
					#ifdef DEBUG
					
						printf ("Second block found at %d, adjusting...\n", i);
					
					#endif
					secondBlockFound = 1;
					ds_file.block[i].start = tempStart + amount;
					ds_file.block[i].length = tempLength - amount;
					ds_file.block[i].alloced = 0;
				}
			}
			return tempStart;
		}			
	}	
	return (-1);
	
}

void ds_free (long start) {
	
	int i;
	int blockFreed = 0;
	
	for (i = 0; i < MAX_BLOCKS; i++) {
		if (ds_file.block[i].start == start && blockFreed == 0) {
			#ifdef DEBUG
			
				printf ("Discovered block %d allocated, freeing...\n", i);
			
			#endif
			ds_file.block[i].alloced = 0;
			blockFreed = 1;
		}
	}
}

void *ds_read (void *ptr, long start, long bytes) {

	if (fseek (ds_file.fp, sizeof(ds_file.block) + start, SEEK_SET) != 0) {
		printf ("Error: could not set file pointer during read\n");
		return NULL;
	}
	if (fread (ptr, bytes, 1, ds_file.fp) != 1) {
		printf ("Error: file could not be read or is empty\n");
		return NULL;
	}
	ds_counts.reads++;
	return ptr;

}

long ds_write (long start, void *ptr, long bytes) {
	
	if (fseek (ds_file.fp, sizeof(ds_file.block) + start, SEEK_SET) != 0) {
		printf ("Error: could not set file pointer during write\n");
		return -1;
	}
	
	if (fwrite (ptr, bytes, 1, ds_file.fp) != 1) {
		printf ("Error: file could not be written into or nothing to write!\n");
		return -1;
	}		
	ds_counts.writes++;
	return (start);
	
}

int ds_finish () {
	
	int i;

	if (fseek (ds_file.fp, 0, SEEK_SET) != 0) {
		printf ("Error: could not set file pointer during finish\n");
		return 0;
	}
	/*Error check when file reads in*/
	/*fwrite (&ds_file, sizeof(ds_file), 0, ds_file.fp);*/
	for (i = 0; i < MAX_BLOCKS; i++) {
		if (fwrite (&ds_file.block[i], sizeof (struct ds_blocks_struct), 1, ds_file.fp) != 1) {
			printf ("Error: file could not be written into or nothing to write!\n");
			return 0;
		}
	}
	printf ("reads: %d\n", ds_counts.reads);
	printf ("writes: %d\n", ds_counts.writes);
	fclose (ds_file.fp);
	return (1);
	
}

