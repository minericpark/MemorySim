#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ds_array.h"
#include "ds_memory.h"
/*#define DEBUG*/
/*#define TEST*/

long elements;

int main(int argc, char **argv) {
	
	
	ds_create ("array.bin", 2048);
	ds_create_array();
	show_array();
	

	/*
	int value;
	long index;

	if(argc!=3)
	{ 
		fprintf( stderr,"Usage:  %svalue index\n", argv[0] );
		return-1;
	}

	value = atoi( argv[1] );
	index = atol( argv[2] );

	ds_init_array();

	ds_insert( value, index );

	ds_finish_array();
	*/

	return 0;
	
}

int ds_create_array() {
	
	if (ds_init("array.bin") == -1) {
		printf ("Error: ds_init failed\n");
		return -1;
	}
	if (ds_malloc(sizeof(long)) == -1) {
		printf ("Error: initial ds_malloc failed\n");
		return -1;
	}
	if (ds_malloc(sizeof(int)*MAX_ELEMENTS) == - 1) {
		printf ("Error: ds_malloc for array failed\n");
		return -1;
	}
	if (ds_finish() != 1) {
		printf ("Error: ds_finish failed\n");
		return -1;
	}
	return 0;
	
}

/*Test function*/
void show_array() {
	
	ds_init_array();
	ds_test_init();
	printf ("elements = %ld", elements);
	ds_finish_array();
	
}

int ds_init_array() {
	
	if (ds_init ("array.bin") != 0) {
		printf ("ds_init failed\n");
		return -1;
	}
	ds_read (&elements, 0, sizeof(long));
	return 0;
	
}

int ds_replace (int value, long index) {
	
	return 0;
}

int ds_insert (int value, long index) {
	
	int oldValue;
	int newValue = value;
	int location;
	int inserted = 0;
	int i;
	
	location = index * sizeof(int) + sizeof(elements);
	
	for (i = index; i < index + elements; i++) {
		if (index == location && inserted == 0) {
			ds_read (&oldValue, index, sizeof(int));
			ds_write (index, &newValue, sizeof(int)); 
			inserted = 1;
		}
		else if (inserted == 1) {
			newValue = oldValue;
			ds_read (&oldValue, index, sizeof(int));
			ds_write (index, &newValue, sizeof(int));
		}
	}
	if (inserted == 0) {
		return -1;
	}
	elements++;
	return 0;
}

int ds_delete (long index) {
	
	return 0;
}

int ds_swap (long index1, long index2) {
	
	return 0;
}

long ds_find (int target) {
	
	return 0;
}

int ds_read_elements (char *filename) {
	
	return 0;
}

int ds_finish_array() {
	
	ds_write (0, &elements, sizeof(long)); 
	if (ds_finish() == 0) {
		printf ("ds_finish failed\n");
		return -1;
	}
	return 0;
}