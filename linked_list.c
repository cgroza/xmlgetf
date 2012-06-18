#include "linked_list.h"

int length_linked_list(linked_list* list)
{
  int i = 0;
  while((list = list -> next) != NULL) i++;
  return i;
}

linked_list* new_linked_list()
{
  linked_list* list = malloc(sizeof(linked_list));
  list -> val = NULL;
  list -> next = NULL;
  return list;
}

void delete_linked_list(linked_list* list)
{
  linked_list* temp = list -> next;
  while(list != NULL)
    {
      free(list -> val);
      free(list);
      list = temp;
      if (list != NULL) temp = list -> next;
    }
}

linked_list* push_linked_list(ezxml_t val, linked_list* list)
{
  /* iterate to last element */
  while(list -> next != NULL) list = list -> next;
  list -> next = new_linked_list();
  list -> next -> val = val;
  return list -> next;
}

