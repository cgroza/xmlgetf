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
#include "extract.h"
#include "linked_list.h"

static void
perform_actions(ezxml_t doc,
                const char* tag, const char* attr, const char* attr_value, 
		const char* entry_sep, int s_attr, int s_tag, int attr_tag_txt)

{
  /* Checks its arguments and calls the necessary functions 
     to extract the data. */
  /* DEBUG info */
  printf("DEBUG: %s %s %d %d\n", tag, attr, s_attr, s_tag);
  linked_list* entries = NULL;

  /* get text of path containing attr */
  if(attr_tag_txt && s_attr && attr != NULL)
    {
      entries = search_attrs(doc, attr, new_linked_list(), attr_value);
      print_field_txt(entries, entry_sep);
    }
  /* get text at named path */
  else if(!s_tag && tag != NULL && attr == NULL)
    {
      entries = get_fields(doc, tag);
      print_field_txt(entries, entry_sep);
    }
  /* get attribute of the named field path */
  else if(!s_tag && tag != NULL && attr != NULL)
    {
    entries = get_fields(doc, tag);
    print_attrs(entries, attr, entry_sep);
    }
  /* get all the fields with the name "tag" */
  else if(s_tag && tag != NULL && attr == NULL)
    {
    entries = search_fields(doc, tag, new_linked_list());
    print_field_txt(entries, entry_sep);
    }
  /* get attribute "attr" from fields named "tag" */
  else if(s_tag && tag != NULL && attr != NULL)
    {
    entries = search_fields(doc, tag, new_linked_list());
    print_attrs(entries, attr, entry_sep);
    }
  /* get all attributes named "attr" */
  else if(s_attr && attr != NULL)
    {
    entries = search_attrs(doc, attr, new_linked_list(), attr_value);
    print_attrs(entries, attr, entry_sep);
    }
  delete_linked_list(entries);
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
