#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ds_list.h"
#include "ds_memory.h"
/*#define DEBUG*/
/*#define TEST*/


int main() {
	
	
	
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

int ds_init_list() {
	
	ds_init ("list.bin");
}

int ds_replace (int value, long index) {
	
	
}

int ds_insert (int value, long index) {
	
	struct ds_list_item_struct previous_item;
	struct ds_list_item_struct new_item;
	long previous_loc = 0;
	int i;
	
	if (fread (previous_item.next, sizeof (long), 1, ds_file.fp) != 1) {
		printf ("Error: file could not be read or is empty");
		return -1;
	}
	for (i = index; i > index; i--) {
		if (previous_item.next == -1) {
			printf ("Error: end of list reached prior to hitting index 0");
			return -1;
		}
		previous_loc = previous_item.next; 
		/*Use address received by previous_item.next to read*/
		fseek (ds_file.fp, previous_loc, SEEK_SET);
		fread (previous_item, sizeof(struct ds_list_item_struct), 1, ds_file.fp);
		
	}

}

int ds_delete (long index) {
	
	
}

int ds_swap (long index1, long index2) {
	
	
}

long ds_find (int target) {
	
	
}

int ds_read_elements (char *filename) {
	
	
}

int ds_finish_list() {
	
	if (ds_finish() != 1) {
		printf ("Error: ds_finish failed\n");
		return -1;
	}
}