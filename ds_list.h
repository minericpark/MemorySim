/*  Eric Minseo Park 
    1001018
    epark03@uoguelph.ca   */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*All function declarations*/
int ds_create_list();
int ds_init_list();
int ds_replace(int value, long index);
int ds_insert(int value, long index);
int ds_delete(long index);
int ds_swap(long index1, long index2);
long ds_find(int target);
int ds_read_elements(char *filename);
int ds_finish_list();

/*
* struct ds_list_item_struct gives
* item index, and address of next item
*/
struct ds_list_item_struct {
	int item;
	long next;
};