#ifndef EXTRACT_H
#define EXTRACT_H

#include <stdio.h>
#include <string.h>
#include "linked_list.h"
#include "ezxml/ezxml.h"

/* Returns all the fields that correspond to the tree path. */
linked_list* get_fields(ezxml_t doc, const char* field);

/* Returns every entry that has the attribute attr. */
linked_list* search_attrs(ezxml_t doc, const char *attr, linked_list* acc,
			  const char* attr_value);

/* Prints the text of the fields contained in tags. */
void print_field_txt(linked_list* tags, const char* entry_sep);

/* Prints the value of the attributes attr contained in tags. */
void print_attrs(linked_list* tags, const char* attr, const char* entry_sep);

/* Returns every entry that has the tag name field. */
linked_list* search_fields(ezxml_t doc, const char *field, linked_list* acc);

#endif
