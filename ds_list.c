#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ds_list.h"
#include "ds_memory.h"
#define DEBUG
/*#define TEST*/


int main() {
	

	ds_create ("list.bin", 2048);


	ds_create_list();


	ds_init_list();

	ds_insert (0,0);
	ds_insert (1,1);
	ds_insert (1,2);
	ds_insert (-1, 0);
	ds_insert (-2, 0);
	ds_insert (-3, 0);
	
	
	ds_test_init();
	show_list();
	ds_finish_list();
	
	return 0;
	
}

int ds_create_list() {
	
	long initial_value;
	long initial_loc;
	
	initial_value = -1;
	
	if (ds_init("list.bin") == -1) {
		#ifdef DEBUG
			printf ("Error: ds_init failed\n");
		#endif
		return -1;
	}
	if ((initial_loc = ds_malloc (sizeof(initial_value))) == -1) {
		#ifdef DEBUG
			printf ("address: %ld", initial_loc);
			printf ("Error: initial ds_malloc failed\n");
		#endif
		return -1;
	}		
	printf ("address: %ld", initial_loc);
	if (ds_write (initial_loc, &initial_value, sizeof(long)) == -1) { /*Checks if ds_write fails*/
		#ifdef DEBUG
			printf ("Error: ds_write failed\n");
		#endif
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

void show_list() {
	
	long loc;
	long loc_check;
	struct ds_list_item_struct li;
	int item_num = 0;
	
	li.item = 0;
	
	printf ("Showing list\n");
	ds_read (&loc, 0, sizeof(long));
	
	do {
		ds_read (&li, loc, sizeof(struct ds_list_item_struct));
		ds_read (&loc_check, loc, sizeof(long));
		loc = li.next;
		printf ("index: %d, value: %d, next: %ld\n", item_num, li.item, li.next);
		item_num++;
	} while (loc_check != -1);
	
}

int ds_init_list() {
	
	if (ds_init ("list.bin") != 0) {
		#ifdef DEBUG
			printf ("ds_init failed\n");
		#endif
		return -1;
	}
	return 0;
}

int ds_replace (int value, long index) {
	
	struct ds_list_item_struct previous_item;
	long previous_loc = 0;
	int i;
	long location;
	location = 1 * sizeof(long);
	
	if (ds_read (&previous_item.next, location, sizeof (long)) == 0) {
		#ifdef DEBUG
			printf ("Error: file could not be read or is empty\n");
		#endif
		return -1;
	}
	for (i = index; i >= 0; i--) {
		if (previous_item.next == -1) {
			#ifdef DEBUG
				printf ("Error: end of list reached prior to hitting index 0\n");
			#endif
			return -1;
		}
		previous_loc = previous_item.next; 	
		/*Use address received by previous_item.next to read*/
		if (ds_read (&previous_item.item, previous_loc, sizeof(int)) == 0) {
			#ifdef DEBUG
				printf ("Error: ds_read failed\n");
			#endif
			return -1;
		}
	}
	if (previous_loc != 0) {
		if (ds_write (previous_loc, &value, sizeof(int)) == -1) {
			#ifdef DEBUG
				printf ("Error: conditional ds_write failed\n");
			#endif
			return -1;
		}
	}
	
	return 0;
}

int ds_insert (int value, long index) {
	
	struct ds_list_item_struct previous_item;
	struct ds_list_item_struct new_item;
	long previous_loc = 0 * sizeof(struct ds_list_item_struct) + sizeof(long);
	long valid = 0;
	int i;
	
	if (ds_read (&previous_item.next, 0, sizeof (long)) == 0) {
		#ifdef DEBUG
			printf ("Error: file could not be read or is empty\n");
		#endif
		return -1;
	} 
	
	for (i = index; i >= 0; i--) {
		if (previous_item.next == -1 && index != 0) {
			#ifdef DEBUG
				printf ("Error: end of list reached prior to hitting index 0\n");
			#endif
			return -1;
		}
		if (index != 0) {
			valid = 0;
			if (ds_write (0, &valid, sizeof(long)) == -1) {
				return -1;
			}
		}
		else {
			valid = -1;
			if (ds_write (0, &valid, sizeof(long)) == -1) {
				return -1;
			}
		}
		previous_loc = previous_item.next; 	
		/*Use address received by previous_item.next to read*/
		if (ds_read (&previous_item, previous_loc, sizeof(struct ds_list_item_struct)) == 0) {
			#ifdef DEBUG
				printf ("Error: ds_read failed\n");
			#endif
			return -1;
		}
	}
	new_item.item = value;
	new_item.next = previous_item.next;
	previous_item.next = ds_malloc(sizeof(new_item));
	if (ds_write (previous_item.next, &new_item, sizeof(struct ds_list_item_struct)) == -1) {
		#ifdef DEBUG
			printf ("Error: ds_write failed\n");
		#endif
		return -1;
	}
	if (previous_loc != 0) {
		if (ds_write (previous_loc, &previous_item, sizeof(struct ds_list_item_struct)) == -1) {
			#ifdef DEBUG
				printf ("Error: conditional ds_write failed\n");
			#endif
			return -1;
		}
	}
	
	return 0;
}

int ds_delete (long index) {
	
	struct ds_list_item_struct previous_item;
	struct ds_list_item_struct new_item;
	long previous_loc = 0;
	int i;
	long location;
	long value;
	location = 1 * sizeof(long);
	
	if (ds_read (&previous_item.next, location, sizeof (long)) == 0) {
		#ifdef DEBUG
			printf ("Error: file could not be read or is empty\n");
		#endif
		return -1;
	}
	for (i = index; i >= 0; i--) {
		if (previous_item.next == -1) {
			#ifdef DEBUG
				printf ("Error: end of list reached prior to hitting index 0\n");
			#endif
			return -1;
		}
		previous_loc = previous_item.next; 	
		/*Use address received by previous_item.next to read*/
		if (ds_read (&previous_item.item, previous_loc, sizeof(int)) == 0) {
			#ifdef DEBUG
				printf ("Error: ds_read failed\n");
			#endif
			return -1;
		}
	}
	new_item.item = value;
	new_item.next = previous_loc;
	previous_item.next = ds_malloc(sizeof(new_item));
	if (ds_write (previous_item.next, &new_item.item, sizeof(int)) == 0) {
		#ifdef DEBUG
			printf ("Error: ds_write failed\n");
		#endif
		return -1;
	}
	if (previous_loc != 0) {
		if (ds_write (previous_loc, &previous_item.item, sizeof(int)) == 0) {
			#ifdef DEBUG
				printf ("Error: conditional ds_write failed\n");
			#endif
			return -1;
		}
	}
	return 0;
	
}

int ds_swap (long index1, long index2) {
	
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
		if (ds_insert	 (value, i) != 0) { /*ds_insert error checker*/
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

int ds_finish_list() {
	
	if (ds_finish() == 0) {
		#ifdef DEBUG
			printf ("Error: ds_finish failed\n");
		#endif
		return -1;
	}
	return 0;
}