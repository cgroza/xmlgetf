/* Copyright (C) 2012 Groza Cristian */

/* This program is free software: you can redistribute it and/or modify */
/* it under the terms of the GNU General Public License as published by */
/* the Free Software Foundation, either version 3 of the License, or */
/* (at your option) any later version. */

/* This program is distributed in the hope that it will be useful, */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the */
/* GNU General Public License for more details. */

/* You should have received a copy of the GNU General Public License */
/* along with this program. If not, see <http://www.gnu.org/licenses/>. */

#include <stdio.h>
#include "ezxml/ezxml.h"
#include <unistd.h>
#include <string.h>
#include "linked_list.h"

static linked_list* get_fields(ezxml_t doc, const char* field)
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

static void 
get_attr_at_field(ezxml_t doc, const char* field, const char* attr,
		  const char* entry_sep)
{
  linked_list* tags = get_fields(doc, field);
  linked_list* head = tags;
  if(tags == NULL) return;
  while(tags != NULL)
    {
      printf("%s\n%s\n", ezxml_attr(tags->val, attr), entry_sep);
      tags = tags -> next;
    }
  delete_linked_list(head);
}

static void
get_text_at_field(ezxml_t doc, const char* field, const char* entry_sep)
{
  linked_list* tags = get_fields(doc, field);
  linked_list* head = tags;
  if(tags == NULL) return;
  while(tags != NULL)
    {
      printf("%s\n%s\n", ezxml_txt(tags->val), entry_sep);
      tags = tags -> next;
    }
  delete_linked_list(head);
}

static linked_list*
search_attrs(ezxml_t doc, const char *attr, linked_list* acc,
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

static void search_attrs_get_attr(ezxml_t doc, const char* attr,
				  const char* attr_val, const char* entry_sep)
{
  linked_list* tags = search_attrs(doc, attr, new_linked_list(), attr_val);
  linked_list* head = tags;
  tags = tags -> next;
  while(tags != NULL) 
    {
      printf("%s\n%s\n", ezxml_attr(tags -> val, attr), entry_sep);
      tags = tags -> next;
    }
  delete_linked_list(head);
}

static void search_attrs_get_txt(ezxml_t doc, const char* attr, 
				 const char* attr_val, const char* entry_sep)
{
  linked_list* tags = search_attrs(doc, attr, new_linked_list(), attr_val);
  linked_list* head = tags;
  tags = tags -> next;
  while(tags != NULL) 
    {
      printf("%s\n%s\n", ezxml_txt(tags -> val), entry_sep);
      tags = tags -> next;
    }
  delete_linked_list(head);
}



static linked_list*
search_fields(ezxml_t doc, const char *field, linked_list* acc)
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

static void
search_fields_get_attr(ezxml_t doc, const char* field, const char* attr,
		       const char* entry_sep)
{
  linked_list* tags = search_fields(doc, field, new_linked_list());
  linked_list* head = tags;
  tags = tags -> next;
  if(tags == NULL) return;
  while(tags != NULL)
    {
      printf("%s\n%s\n", ezxml_attr(tags->val, attr), entry_sep);
      tags = tags -> next;
    }
  delete_linked_list(head);

}

static void
search_fields_get_txt(ezxml_t doc, const char* field, const char* entry_sep)
{
  linked_list* tags = search_fields(doc, field, new_linked_list());
  linked_list* head = tags;
  tags = tags -> next;
  if(tags == NULL) return;
  while(tags != NULL)
    {
      printf("%s\n%s\n", ezxml_txt(tags->val), entry_sep);
      tags = tags -> next;
    }
  delete_linked_list(head);
}

static void
perform_actions(ezxml_t doc,
                const char* tag, const char* attr, const char* attr_value, 
		const char* entry_sep, int s_attr, int s_tag, int attr_tag_txt)

{
  /* Checks its arguments and calls the necessary functions 
     to extract the data. */
  /* DEBUG info */
  printf("DEBUG: %s %s %d %d\n", tag, attr, s_attr, s_tag);

  /* get text of path containing attr */
  if(attr_tag_txt && s_attr && attr != NULL)
    search_attrs_get_txt(doc, attr, attr_value, entry_sep);
  /* get text at named path */
  else if(!s_tag && tag != NULL && attr == NULL)
    get_text_at_field(doc, tag, entry_sep);
  /* get attribute of the named field path */
  else if(!s_tag && tag != NULL && attr != NULL)
    get_attr_at_field(doc, tag, attr, entry_sep);
  /* get all the fields with the name "tag" */
  else if(s_tag && tag != NULL && attr == NULL)
    search_fields_get_txt(doc, tag, entry_sep);
  /* get attribute "attr" from fields named "tag" */
  else if(s_tag && tag != NULL && attr != NULL)
    search_fields_get_attr(doc, tag, attr, entry_sep);
  /* get all attributes named "attr" */
  else if(s_attr && attr != NULL)
    search_attrs_get_attr(doc, attr, attr_value, entry_sep);
}

int main(int argc, char* argv[])
{
  /* store attr and tag names */
  char* tag_name = NULL;
  char* attr_name = NULL;
  char* attr_value = NULL;
  char* entry_seprator = NULL;
  /* bools to determine whether whe should search for an exact path in 
     the xml, or scan all the fields/tags in order to find one that has
     the required name */
  int search_attr = 0;
  int search_tag  = 0;
  int attr_tag_txt = 0;		/* this will make the program return the text
				 of the entry that contains the argument.*/

  /* parse command line arguments and set variables */
  char c;
  while((c = getopt(argc, argv, "s:a:t:A:T:v:c")) != -1)
    {
      switch(c)
	{
	case 'a':
	  attr_name = optarg;
	  break;

	case 't':
	  tag_name = optarg;
	  break;

	case 'A':
	  search_attr = 1;	/* attr will be searched */
	  attr_name = optarg;
	  break;

	case 'T':
	  search_tag = 1;	/* tag will be searched */
	  tag_name = optarg;
	  break;

	case 'c':
	  attr_tag_txt = 1;
	  break;

	case 'v':
	  attr_value = optarg;
	  break;

	case 's':
	  entry_seprator = optarg;
	  break;

	default:
	  printf("Invalid use of arguments. Please consult the documentation.\n");
	  exit(-1);
	  break;
	}
    }
  /* get target file and parse xml document*/
  const char* doc_file = argv[argc-1];
  ezxml_t xml_doc = ezxml_parse_file(doc_file);
  /* check if document was parsed successfuly */
  if(xml_doc == NULL)
    {
      printf("Failed to parse document %s", doc_file);
      return -1;
    }

  if(entry_seprator == NULL) entry_seprator = "--------------------------------";
  perform_actions(xml_doc, tag_name, attr_name, attr_value, entry_seprator,
		  search_attr, search_tag, attr_tag_txt);
  printf("DEBUG: %s\n", doc_file);
  return 0;
}
