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

List *list_search (List *list, List* (*compare_function) (List *list, void *value), void *compare_value) 
{
	while(list != NULL)
	{
		if(isdigit(compare_value))
		{
			int int_value = *(int*) compare_value; 
			compare_function(list,int_value);
		}
		else {
			char* string_value = (char*) compare_value;
			compare_function(list,string_value);
			
		}
	}
}

void list_free_all(List *list, void (*free_function)(List *list))
{
	list = list_find_first(list);
	while(list != NULL)
	{	
	/*	free(list->prev);	
		free_function(list);
		free(list->data);		
		free(list->next);*/
		free(list);    
		list = list->next;	
	}

}
