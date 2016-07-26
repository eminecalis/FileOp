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

List *insert (List *list, void *contact);
#endif //FILEOP_LIST_H
