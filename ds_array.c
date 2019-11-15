/*  Eric Minseo Park 
    1001018
    epark03@uoguelph.ca   */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ds_array.h"
#include "ds_memory.h"
/*#define DEBUG*/
/*#define TEST*/

long elements;

/*
int main(int argc, char **argv) {
	

	int value;
	long index;

	ds_create ("array.bin", 2048);
	#ifdef DEBUG
		printf ("Before ds_create_array\n");
	#endif
	ds_create_array();
	#ifdef DEBUG
		printf ("Before ds_read_elements\n");
	#endif
	show_memory();
	ds_init_array();


	if(argc!=3)
	{ 
		fprintf( stderr,"Usage:  %svalue index\n", argv[0] );
		return-1;
	}

	value = atoi( argv[1] );
	index = atol( argv[2] );

	ds_read_elements ("test.txt");

	ds_insert (110, 4);
	ds_replace(  120, 3 );

	#ifdef DEBUG
		printf ("Before ds_read_elements\n");
	#endif

	ds_delete (6);
	
	show_array();

	ds_finish_array();

	return 0;
	
}
*/

/*
* int ds_create_array initializes array.bin,
* mallocs size of long elements, mallocs elements of MAX_ELEMENTS,
* and writes elements into file. Ends with finish. Returns 0 when success, and -1 when failed.
*/
int ds_create_array() {
	
	elements = 0;
	long elements_loc;
	
	if (ds_init("array.bin") == -1) {
		#ifdef DEBUG
			printf ("Error: ds_init failed\n");
		#endif
		return -1;
	}
	if ((elements_loc = ds_malloc (sizeof(elements))) == -1) {
		#ifdef DEBUG
			printf ("Error: initial ds_malloc failed\n");
		#endif
		return -1;
	}
	if (ds_malloc (sizeof(int) * MAX_ELEMENTS) == -1) {
		#ifdef DEBUG
			printf ("Error: ds_malloc for array failed\n");
		#endif
		return -1;
	}
	if (ds_write (elements_loc, &elements, sizeof(long)) == -1) { /*Checks if ds_write fails*/
		return -1;
	}
	if (ds_finish() != 1) {
		#ifdef DEBUG
			printf ("Error: ds_finish failed\n");
		#endif
		return -1;
	}
	return 0;
	
}

/*
* int ds_init_array ds_inits array.bin, and 
* reads into elements the first long in file (which should be where element is stored in)
* returns 0 when success and -1 when fail.
*/
int ds_init_array() {
	
	if (ds_init ("array.bin") != 0) {
		#ifdef DEBUG
			printf ("ds_init failed\n");
		#endif
		return -1;
	}
	if (ds_read (&elements, 0, sizeof(long)) == 0) { /*Checks if ds_read fails*/
		return -1;
	}
	return 0;
	
}

/*
* int ds_replace takes in int value and long index, and finds location (with use of index), and writes into location
* the value provided. Returns 0 when success, -1 when fail.
*/
int ds_replace (int value, long index) {
	
	long location;
	
	if (index < 0 || index >= elements) { /*Checks if index is negative or greater + equal to current size of array*/
		return -1;
	}
	
	location = index * sizeof(int) + sizeof(elements);
	#ifdef DEBUG
		printf ("value: %d location: %ld\n", value, location);
	#endif
	if (ds_write (location, &value, sizeof(int)) == -1) { /*Checks if ds_write fails*/
		return -1;
	}
	
	return 0;
}

/*
* int ds_insert takes in int value, long index, and inserrts into array (at location given by index)
* the value provided. Returns 0 when success, and -1 when fail.
*/
int ds_insert (int value, long index) {
	
	long oldValue;
	long newValue;
	long location;
	int inserted;
	int i;
	
	newValue = value;
	inserted = 0;
	
	if (elements + 1 > MAX_ELEMENTS) { /*Determines if elements has reached maximum capacity*/
		return -1;
	}
	
	if (index < 0 || index > elements) { /*Determine if index is negative or greater than elements*/
		return -1;
	}
	
	/*For loop scans entire array from index and calculates location, writes in and temporarily stores first element, then reads and writes appropriately to push array up by one*/
	for (i = index; i <= elements; i++) {
		#ifdef DEBUG
			printf ("Before - New: %ld, old %ld\n", newValue, oldValue);
		#endif
		location = i * sizeof(int) + sizeof(elements); /*Calculate location of int stored at index num*/
		#ifdef DEBUG
			printf ("%d location: %ld\n", i, location);
		#endif
		if (ds_read (&oldValue, location, sizeof(int)) == 0) { /*Checks if ds_read fails*/
			return -1;
		}
		if (ds_write (location, &newValue, sizeof(int)) == -1) { /*Checks if ds_write fails*/
			return -1;
		}
		
		newValue = oldValue;
		#ifdef DEBUG
			printf ("After - New: %ld, old %ld\n", newValue, oldValue);
		#endif
		inserted = 1;
	}
	
	if (inserted == 0) {
		#ifdef DEBUG
			printf ("Insert failed\n");
		#endif
		return -1;
	}
	elements++;
	return 0;
}

/*
* int ds_delete takes long index, and finds location with index
* and deletes (reads, then writes over) the object at index. 
* Returns 0 when success, -1 when fail.
*/
int ds_delete (long index) {
	
	long curr_loc;
	long next_loc;
	long value;
	int removed;
	int i;
	
	if (index < 0 || index >= elements) { /*Checks if index is negative or greater/equal to current size of array, and returns -1*/
		return -1;
	}
	
	/*For loop covers entire array from index to end and records current location, then next location, and reads into the current 
	value the value at next location, and writes value at next location, into current location. Sets removed bool to true (1)*/
	for (i = index; i < elements; i++) {
		curr_loc = i * sizeof(int) + sizeof(elements);
		next_loc = (i + 1) * sizeof(int) + sizeof(elements);
		if (ds_read (&value, next_loc, sizeof(int)) == 0) { /*Checks if ds_read fails*/
			return -1;
		}
		if (ds_write (curr_loc, &value, sizeof(int)) == -1) { /*Checks if ds_write fails*/
			return -1;
		}
		removed = 1;
	}
	
	if (index == elements - 1) { /*Checks if the index requested to be deleted is last element of array, and removes 1 from element, and returns success (0)*/
		elements--; 
		return 0;
	}

	if (removed == 0) { /*Checks if removed bool is false (0). If false, returns -1*/
		#ifdef DEBUG
			printf ("Deleted failed\n");
		#endif
		return -1;
	}
	elements--; /*Subtract elements by 1*/

	return 0;
}

/*
* int ds_swap takes in long index1 and long index2 to swap 
* the values by finding both locations with index1 and index2,
* then reads and writes the previous values with swapped locations.
* Returns 0 when success, -1 when fail.
*/
int ds_swap (long index1, long index2) {
	
	long loc_1;
	long loc_2;
	long val_1;
	long val_2;
	
	if (index1 < 0 || index1 >= elements || index2 < 0 || index2 >= elements) { /*Checks if either index1 or index2 are either negative or greater than current size of array, and returns -1*/
		return -1;
	}
	
	/*Finds locations of both index, and reads their appropriate values, then swaps by writing them into the other location*/
	loc_1 = index1 * sizeof(int) + sizeof(elements);
	loc_2 = index2 * sizeof(int) + sizeof(elements);
	
	if (ds_read (&val_1, loc_1, sizeof(int)) == 0) { /*Checks if ds_read fails*/
		return -1;
	}
	if (ds_read (&val_2, loc_2, sizeof(int)) == 0) { /*Checks if ds_read fails*/
		return -1;
	}
	
	if (ds_write (loc_1, &val_2, sizeof(int)) == -1) { /*Checks if ds_write fails*/
		return -1;
	}
	if (ds_write (loc_2, &val_1, sizeof(int)) == -1) { /*Checks if ds_write fails*/
		return -1;
	}
	return 0;
}

/*
* long ds_finish takes in int target, and scans through
* array to find match for target, and returns index when success,
* and -1 when fail.
*/
long ds_find (int target) {
	
	int i;
	long index_loc;
	int curr;
	
	/*For loop scans entire array (using read) to discover a match with target, then returns that index number*/
	for (i = 0; i < elements; i++) {
		index_loc = i * sizeof(int) + sizeof(elements);
		if (ds_read (&curr, index_loc, sizeof(int)) == 0) { /*Checks if ds_read fails*/
			return -1;
		}
		if (curr == target) {
			return i;
		}
	}
	return -1;
}

/*
* int ds_read_elements takes in char filename and reads all elements from read_elements
* and inserts them into the array. Returns 0 when success, -1 when fail.
*/
int ds_read_elements (char *filename) {
	
	FILE *fp;
	int i;
	int value;
	
	i = 0;
	
	if ((fp = fopen (filename, "r+")) == 0) { /*File open checker*/
		#ifdef DEBUG
			printf ("Error: file could not be opened\n");
		#endif
		return -1;
	}
	if (fseek (fp, 0, SEEK_SET) != 0) { /*Set file pointer at beginning*/
		return -1;
	}
	
	while (fscanf (fp, "%d", &value) > 0) { /*While loop continues to scan while pointer has not reached end of file, inserts every value compatible and increments i counter by 1*/
		if (ds_insert (value, i) != 0) { /*ds_insert error checker*/
			return -1;
		}
		i++;
	}
	if (fclose (fp) == EOF) { /*File close checker*/
		#ifdef DEBUG
			printf ("Error: file could not be closed\n");
		#endif
		return -1;
	}
	return 0;
}

/*
* int ds_finish_array writes elements into file and calls
* ds_finish. Returns 0 when success and -1 when fail
*/
int ds_finish_array() {
	
	if (ds_write (0, &elements, sizeof(long)) == -1) { /*Checks if ds_write fails*/
		return -1;
	} 
	if (ds_finish() == 0) { /*Checks if ds_finish fails*/
		#ifdef DEBUG
			printf ("ds_finish failed\n");
		#endif
		return -1;
	}
	return 0;
}