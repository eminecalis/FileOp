//
// Created by sebastiangeiger on 26/07/16.
//

#include "list.h"
#include <stdlib.h>
List *insert (List *list, void *data) {
  List *item;
  item = malloc(sizeof(List));
  item->next =NULL;
  item->prev = list;

  if(list!= NULL) {

    list->next = item;
  }
  item->data = data;
  return item;

}

List *list_find_first(List *list)
{
	while(list->prev!= NULL)
	{
		list = list->prev;
	}
	return list;
}

void list_for_each(List *list, void (*callback) (List *list))
{
	while(list != NULL)
  {   
   callback(list);
   list = list->next;
  }	

}

List *list_search (List *list, int (*compare_function) (List *list, void *value), void *compare_value)
{
	list = list_find_first (list);

	while(list != NULL)
	{
		if(compare_function(list, compare_value) == 0)
		{
			return list;
		}

		list = list->next;
	}
	return NULL;
}

void list_free_all(List *list, void (*free_function)(void *data))
{
	list = list_find_first(list);
	while(list != NULL)
	{
		List *temp = list->next;
		free_function(list->data);
		list->data = NULL;
		list->prev = NULL;
		list->next = NULL;
		free(list);


		list = temp;
	}

}
