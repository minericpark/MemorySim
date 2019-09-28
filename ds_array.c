#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ds_array.h"
#include "ds_memory.h"
#define DEBUG
/*#define TEST*/

long elements;

int main(int argc, char **argv) {
	
	/*
	ds_create ("array.bin", 2048);
	ds_create_array();
	show_memory();
	*/

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
	ds_init_array();

/*
	if(argc!=3)
	{ 
		fprintf( stderr,"Usage:  %svalue index\n", argv[0] );
		return-1;
	}

	value = atoi( argv[1] );
	index = atol( argv[2] );
*/
/*
	ds_insert (value, index);
	ds_replace( value, index );
*/
	#ifdef DEBUG
		printf ("Before ds_read_elements\n");
	#endif
	
	ds_read_elements ("test.txt");
	ds_swap (0, 1);
	
	show_array();

	ds_finish_array();

	return 0;
	
}

int ds_create_array() {
	
	elements = 0;
	long elements_loc;
	
	if (ds_init("array.bin") == -1) {
		#ifdef DEBUG
			printf ("Error: ds_init failed\n");
		#endif
		return -1;
	}
	elements_loc = ds_malloc (sizeof(elements));
	if (elements_loc == -1) {
		#ifdef DEBUG
			printf ("Error: initial ds_malloc failed\n");
		#endif
		return -1;
	}
	ds_write (elements_loc, &elements, sizeof(long));
	if (ds_malloc(sizeof(int)*MAX_ELEMENTS) == - 1) {
		#ifdef DEBUG
			printf ("Error: ds_malloc for array failed\n");
		#endif
		return -1;
	}
	if (ds_finish() != 1) {
		printf ("Error: ds_finish failed\n");
		return -1;
	}
	return 0;
	
}

/*Test function*/
void show_memory() {
	
	printf ("Showing memory");
	ds_init_array();
	ds_test_init();
	printf ("elements = %ld", elements);
	ds_finish_array();
	
}

/*Test function*/
void show_array() {
	
	int i;
	int value;
	long location;
	
	printf ("elements = %ld\n", elements);
	printf ("Showing array\n");
	for (i = 0; i < elements; i++) {
		location = i * sizeof(int) + sizeof(elements);
		printf ("location: %ld\n", location);
		ds_read (&value, location, sizeof(int));	
		printf ("%d %d\n", i, value); 
	}
	
}

int ds_init_array() {
	
	if (ds_init ("array.bin") != 0) {
		#ifdef DEBUG
			printf ("ds_init failed\n");
		#endif
		return -1;
	}
	ds_read (&elements, 0, sizeof(long));
	return 0;
	
}

int ds_replace (int value, long index) {
	
	long location;
	
	location = index * sizeof(int) + sizeof(elements);
	#ifdef DEBUG
		printf ("value: %d location: %ld\n", value, location);
	#endif
	ds_write (location, &value, sizeof(int));
	
	return 0;
}

int ds_insert (int value, long index) {
	
	long oldValue;
	long newValue;
	long location;
	int inserted;
	int i;
	
	newValue = value;
	inserted = 0;
	
	for (i = index; i <= elements; i++) {
		#ifdef DEBUG
			printf ("Before - New: %ld, old %ld\n", newValue, oldValue);
		#endif
		location = i * sizeof(int) + sizeof(elements);
		#ifdef DEBUG
			printf ("%d location: %ld\n", i, location);
		#endif
		ds_read (&oldValue, location, sizeof(int));
		ds_write (location, &newValue, sizeof(int));
		
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

int ds_delete (long index) {
	
	long curr_loc;
	long next_loc;
	long value;
	int removed;
	int i;
	
	if (index < 0 || index > elements - 1) {
		return -1;
	}
	
	for (i = index; i < elements - 1; i++) {
		curr_loc = i * sizeof(int) + sizeof(elements);
		next_loc = (i + 1) * sizeof(int) + sizeof(elements);
		ds_read (&value, next_loc, sizeof(int));
		ds_write (curr_loc, &value, sizeof(int));
		removed = 1;
	}

	if (removed == 0) {
		#ifdef DEBUG
			printf ("Deleted failed\n");
		#endif
		return -1;
	}
	elements--;

	return 0;
}

int ds_swap (long index1, long index2) {
	
	/*Convert 2 indices into addresses, read the 2 values from the addresses into two temp variables, then write them to their opposite addresses*/
	long loc_1;
	long loc_2;
	long val_1;
	long val_2;
	
	if (index1 < 0 || index1 > elements - 1 || index2 < 0 || index2 > elements - 1) {
		return -1;
	}
	
	loc_1 = index1 * sizeof(int) + sizeof(elements);
	loc_2 = index2 * sizeof(int) + sizeof(elements);
	
	ds_read (&val_1, loc_1, sizeof(int));
	ds_read (&val_2, loc_2, sizeof(int));
	
	ds_write (loc_1, &val_2, sizeof(int));
	ds_write (loc_2, &val_1, sizeof(int));
	
	return 0;
}

long ds_find (int target) {
	
	return 0;
}

int ds_read_elements (char *filename) {
	
	FILE *fp;
	int i;
	int value;
	
	i = 0;
	
	if ((fp = fopen (filename, "r+")) == NULL) { /*File checker*/
		#ifdef DEBUG
			printf ("Error: file could not be opened\n");
		#endif
		return -1;
	}
	fseek (fp, 0, SEEK_SET);
	
	while (fscanf (fp, "%d", &value) > 0) {
		ds_insert (value, i);
		i++;
	}
	if (fclose (fp) == EOF) {
		#ifdef DEBUG
			printf ("Error: file could not be closed\n");
		#endif
		return -1;
	}
	return 0;
}

int ds_finish_array() {
	
	ds_write (0, &elements, sizeof(long)); 
	if (ds_finish() == 0) {
		#ifdef DEBUG
			printf ("ds_finish failed\n");
		#endif
		return -1;
	}
	return 0;
}