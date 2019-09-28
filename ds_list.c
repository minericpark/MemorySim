#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ds_list.h"
#include "ds_memory.h"
/*#define DEBUG*/
/*#define TEST*/


int main() {
	
	return 0;
	
}

int ds_create_list() {
	
	long initialValue = -1;
	
	if (ds_init("list.bin") == -1) {
		printf ("Error: ds_init failed\n");
		return -1;
	}
	if (ds_malloc(-1) == sizeof(initialValue)) {
		printf ("Error: initial ds_malloc failed\n");
		return -1;
	}		
	if (ds_finish() != 1) {
		printf ("Error: ds_finish failed\n");
		return -1;
	}
	return 0;
	
	
}

void show_list() {
	
	long loc;
	struct ds_list_item_struct li;
	int i;
	
	i = 0;
	
	ds_test_init();
	ds_read (loc, 0, sizeof (long));
	while (i > -1) {
		ds_read (&li, loc, sizeof(struct ds_list_item_struct));
		loc = li.next;
		
	}		
	
}

int ds_init_list() {
	
	if (ds_init ("list.bin") != 0) {
		printf ("ds_init failed\n");
		return -1;
	}
	return 0;
}

int ds_replace (int value, long index) {
	
	return 0;
}

int ds_insert (int value, long index) {
	
	struct ds_list_item_struct previous_item;
	struct ds_list_item_struct new_item;
	long previous_loc = 0;
	int i;
	long location;
	location = 1 * sizeof(int);
	
	if (ds_read (&previous_item.next, location, sizeof (long)) != 1) {
		printf ("Error: file could not be read or is empty");
		return -1;
	}
	for (i = index; i > 0; i--) {
		if (previous_item.next == -1) {
			printf ("Error: end of list reached prior to hitting index 0");
			return -1;
		}
		previous_loc = previous_item.next; 	
		/*Use address received by previous_item.next to read*/
		ds_read (previous_item.item, previous_loc, sizeof(int));
	}
	new_item.item = value;
	new_item.next = previous_loc;
	previous_item.next = ds_malloc(new_item.item);
	ds_write (previous_item.next, new_item.item, sizeof(int));
	if (previous_loc != 0) {
		ds_write (previous_loc, &previous_item, sizeof(struct ds_list_item_struct)); 
	}
	
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

int ds_finish_list() {
	
	if (ds_finish() != 1) {
		printf ("Error: ds_finish failed\n");
		return -1;
	}
	return 0;
}