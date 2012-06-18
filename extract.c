#include "extract.h"

linked_list* get_fields(ezxml_t doc, const char* field)
{
  char* cur_field = strtok((char*) field, "/");
  char* temp_field = NULL;	/* temporary for field */
  ezxml_t cur_tag = doc;
  if (cur_field == NULL) return NULL;
  while((temp_field = strtok(NULL, "/")) != NULL)
    {
      cur_field = temp_field;	/* temp_field not null, use it as cur_field */
      cur_tag = ezxml_child(cur_tag, cur_field);
    }
  if(cur_tag != doc)
    {
      linked_list* tags = new_linked_list();
      tags -> val = cur_tag;
      while((cur_tag = ezxml_next(cur_tag)) != NULL)
	push_linked_list(cur_tag, tags);
      return tags;
    }
  else return NULL;
}

linked_list* search_attrs(ezxml_t doc, const char *attr, linked_list* acc,
	     const char* attr_value)
{
  ezxml_t iterator = NULL;
  if(attr_value == NULL)
    {
      if(ezxml_attr(doc, attr) != NULL) push_linked_list(doc, acc);
    }
  else
    {
      const char* value = ezxml_attr(doc, attr);
      if(value != NULL && strcmp(value, attr_value) == 0)
	push_linked_list(doc, acc);
    }

  iterator = doc -> child;
  while(iterator != NULL)
    {
      search_attrs(iterator, attr, acc, attr_value);
      iterator = iterator -> ordered;
    }
  return acc;
}

void print_field_txt(linked_list* tags, const char* entry_sep)
{
  if(tags -> val == NULL) tags = tags -> next;
  if(tags == NULL) return;
  while(tags != NULL)
    {
      printf("%s\n%s\n", ezxml_txt(tags->val), entry_sep);
      tags = tags -> next;
    }
}

void print_attrs(linked_list* tags, const char* attr, const char* entry_sep)
{
  if(tags -> val == NULL) tags = tags -> next;
  while(tags != NULL) 
    {
      printf("%s\n%s\n", ezxml_attr(tags -> val, attr), entry_sep);
      tags = tags -> next;
    }
}

linked_list* search_fields(ezxml_t doc, const char *field, linked_list* acc)
{
  ezxml_t iterator = NULL;
  ezxml_t child = ezxml_child(doc, field);
  while(child != NULL)
    {
      push_linked_list(child, acc);
      child = ezxml_next(child);
    }
  /* now call search fields for every child. we travers the tree this way */
  iterator = doc -> child;
  while(iterator != NULL) 
    {
      search_fields(iterator, field, acc);
      iterator = iterator -> ordered;
    }
  return acc;
}

