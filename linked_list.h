#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "ezxml/ezxml.h"

typedef struct linked_list_t
{
  ezxml_t val;
  struct linked_list_t* next; 
} linked_list;

/* returns the list length */
int length_linked_list(linked_list* list);

/* creates a new linked list node */
linked_list* new_linked_list();

/* deletes every node of list and its values */
void delete_linked_list(linked_list* list);

/* Adds val at the end of the list and returns the last node */
linked_list* push_linked_list(ezxml_t val, linked_list* list);
#endif
