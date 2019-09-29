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
	struct ds_list_item_struct li;
	int item_num = 0;
	int i;
	int size = 6;
	
	li.item = 0;
	
	printf ("Showing list\n");
	ds_read (&loc, 0, sizeof(long));
	
	for (i = 0; i < size; i++) {
		ds_read (&li, loc, sizeof(struct ds_list_item_struct));
		printf ("address: %ld, value: %d, next: %ld\n", loc, li.item, loc);
		loc = li.next;
	}
	
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
	
	struct ds_list_item_struct temp_struct;
	int i;
	long header = 0;
	long temp_loc;
	
	if (ds_read (&temp_loc, 0, sizeof(long)) == 0) { /*Read address of first item in linkedlist*/
		#ifdef DEBUG
			printf ("ds_read failed\n");
		#endif
		return -1;
	}
	
	for (i = index; i >= 0; i--) { /*Scan through list starting at index to seek value previous to it and set temp_loc*/
		header = temp_loc;
		if (ds_read (&temp_struct, header, sizeof(struct ds_list_item_struct)) == 0) {
			#ifdef DEBUG
				printf ("ds_read failed\n");
			#endif
			return -1;
		}
		temp_loc = temp_struct.next;
	}
	
	if ((temp_struct.next = ds_malloc (sizeof(temp_struct))) == -1) { /*Malloc appropriate size to struct*/
		#ifdef DEBUG
			printf ("ds_malloc failed\n");
		#endif
		return -1;
	}
	
	if (header == 0) { /*If header is still 0, write only long*/
		if (ds_write (header, &temp_struct.next, sizeof(long)) == -1) {
			#ifdef DEBUG
				printf ("ds_Write failed\n");
			#endif
			return -1;
		}			
	}
	else { /*Else write only struct*/
		if (ds_write (header, &temp_struct, sizeof(struct ds_list_item_struct)) == -1) {
			#ifdef DEBUG
				printf ("ds_write failed\n");
			#endif
			return -1;
		}
	}
	
	/*Set values of new_item object and malloc*/
	header = temp_struct.next;
	temp_struct.next = temp_loc;
	temp_struct.item = value;
	
	/*Write appropriate node into file*/
	if (ds_write (header, &temp_struct, sizeof(struct ds_list_item_struct)) == -1) {
		#ifdef DEBUG
			printf ("ds_write failed\n");
		#endif
		return -1;
	}
	
	return 0;
	
}

int ds_insert (int value, long index) {
	
	struct ds_list_item_struct temp_struct;
	int i;
	long header = 0;
	long temp_loc;
	
	if (ds_read (&temp_loc, 0, sizeof(long)) == 0) { /*Read address of first item in linkedlist*/
		#ifdef DEBUG
			printf ("ds_read failed\n");
		#endif
		return -1;
	}
	
	for (i = index; i > 0; i--) { /*Scan through list starting at index to seek value previous to it and set temp_loc*/
		header = temp_loc;
		if (ds_read (&temp_struct, header, sizeof(struct ds_list_item_struct)) == 0) {
			#ifdef DEBUG
				printf ("ds_read failed\n");
			#endif
			return -1;
		}
		temp_loc = temp_struct.next;
	}
	
	if ((temp_struct.next = ds_malloc (sizeof(temp_struct))) == -1) { /*Malloc appropriate size to struct*/
		#ifdef DEBUG
			printf ("ds_malloc failed\n");
		#endif
		return -1;
	}
	
	if (header == 0) { /*If header is still 0, write only long*/
		if (ds_write (header, &temp_struct.next, sizeof(long)) == -1) {
			#ifdef DEBUG
				printf ("ds_Write failed\n");
			#endif
			return -1;
		}			
	}
	else { /*Else write only struct*/
		if (ds_write (header, &temp_struct, sizeof(struct ds_list_item_struct)) == -1) {
			#ifdef DEBUG
				printf ("ds_write failed\n");
			#endif
			return -1;
		}
	}
	
	/*Set values of new_item object and malloc*/
	header = temp_struct.next;
	temp_struct.next = temp_loc;
	temp_struct.item = value;
	
	/*Write appropriate node into file*/
	if (ds_write (header, &temp_struct, sizeof(struct ds_list_item_struct)) == -1) {
		#ifdef DEBUG
			printf ("ds_write failed\n");
		#endif
		return -1;
	}
	
	return 0;
}

int ds_delete (long index) {
	
	struct ds_list_item_struct temp_struct;
	int i;
	long header = 0;
	long temp_loc;
	
	if (ds_read (&temp_loc, 0, sizeof(long)) == 0) { /*Read address of first item in linkedlist*/
		#ifdef DEBUG
			printf ("ds_read failed\n");
		#endif
		return -1;
	}
	
	for (i = index; i > 0; i--) { /*Scan through list starting at index to seek value previous to it and set temp_loc*/
		header = temp_loc;
		if (ds_read (&temp_struct, header, sizeof(struct ds_list_item_struct)) == 0) {
			#ifdef DEBUG
				printf ("ds_read failed\n");
			#endif
			return -1;
		}
		temp_loc = temp_struct.next;
	}
	
	ds_free (temp_struct.next);
	
	if (header == 0) { /*If header is still 0, write only long*/
		if (ds_write (header, &temp_struct.next, sizeof(long)) == -1) {
			#ifdef DEBUG
				printf ("ds_Write failed\n");
			#endif
			return -1;
		}			
		
	}
	else { /*Else write only struct*/
	
		/**/
		if (ds_write (header, &temp_struct, sizeof(struct ds_list_item_struct)) == -1) {
			#ifdef DEBUG
				printf ("ds_write failed\n");
			#endif
			return -1;
		}
	}
	
	/*Set values of new_item object and malloc*/
	header = temp_struct.next;
	temp_struct.next = temp_loc;
	temp_struct.value = value;
	
	/*Write appropriate node into file*/
	if (ds_write (header, &temp_struct, sizeof(struct ds_list_item_struct)) == -1) {
		#ifdef DEBUG
			printf ("ds_write failed\n");
		#endif
		return -1;
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
	
	/**/
	
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