#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ds_array.h"
#include "ds_memory.h"
/*#define DEBUG*/
/*#define TEST*/

long element;

int main() {
	
	ds_create ("array.bin", 2048);
	ds_create_array();
	show_array();
	return 0;
	
}

int ds_create_array() {
	
	if (ds_init("array.bin") == -1) {
		printf ("Error: ds_init failed");
		return -1;
	}
	if (ds_malloc(sizeof(long)) == -1) {
		printf ("Error: initial ds_malloc failed");
		return -1;
	}
	if (ds_malloc(sizeof(int)*MAX_ELEMENTS) == - 1) {
		printf ("Error: ds_malloc for array failed");
		return -1;
	}
	if (ds_finish() != 1) {
		printf ("Error: ds_finish failed");
		return -1;
	}
	return 0;
	
}

/*Test function*/
void show_array() {
	
	ds_test_init();
	printf ("elements = %ld", element);
	
}

int ds_init_array() {
	
	return 0;
	
}

int ds_replace (int value, long index) {
	
	return 0;
}

int ds_insert (int value, long index) {
	
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
	
	return 0;
}