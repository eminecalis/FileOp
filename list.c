//
// Created by sebastiangeiger on 26/07/16.
//

#include "list.h"
#include <stdlib.h>
List *insert (List *list, void *contact) {
  List *item;
  item = malloc(sizeof(List));
  item->next =NULL;
  item->prev = list;

  if(list!= NULL) {

    list->next = item;
  }
  item->data = contact;
  return item;

}
