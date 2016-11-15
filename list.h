//
// Created by sebastiangeiger on 26/07/16.
//

#ifndef FILEOP_LIST_H
#define FILEOP_LIST_H

typedef struct list{
  struct list *prev;
  struct list *next;
  void        *data;
}List;

List *insert (List *list, void *data);

List *list_find_first(List *list);

void list_for_each(List *list, void (*callback) (List *list));

List *list_search (List *list, int (*compare_function) (List *list, void *value), void *compare_value);

void list_free_all(List *list, void (*free_function)(void *data));

#endif //FILEOP_LIST_H
