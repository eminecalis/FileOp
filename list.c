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

void list_for_each(List *list, void (*callback) (List *mylist))
{
	while(list != NULL)
  {   
   callback(list);
   list = list->next;
  }	

}
