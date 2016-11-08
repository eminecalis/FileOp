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

List *list_search (List *list, void (*compare_function) (List *list, void *value), void *compare_value) 
{
	while(list != NULL)
	{
		if(isdigit(compare_value))
		{
			list = compare_by_index(list,compare_value);
		}
		else
		{	if(compare_by_name(list,compare_value))		
			list = compare_by_name(list,compare_value);
			elseif(compare_by_telefonnumber(list,compare_value));
			list = compare_by_telefonnumber(list,compare_value);
		}
	}
}
