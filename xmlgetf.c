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

static ezxml_t get_fields(ezxml_t doc, const char* field)
{
  char* cur_field = strtok((char*) field, "/");
  char* temp_field = NULL;	/* temporary for field */
  ezxml_t cur_tag = doc;
  if (cur_field == NULL) return;
  while((temp_field = strtok(NULL, "/")) != NULL)
    {
      cur_field = temp_field;	/* temp_field not null, use it as cur_field */
      cur_tag = ezxml_child(cur_tag, cur_field);
    }
  return (cur_tag != doc ? cur_tag : NULL);
}

static char* 
get_attr_at_field(ezxml_t doc, const char* field, const char* attr)
{
}

static char*
get_text_at_field(ezxml_t doc, const char* field)
{
  return ezxml_txt(get_fields(doc, field));
}

static char*
search_attrs(ezxml_t doc, const char *attr)
{
}

static char*
search_fields(ezxml_t doc, const char *field)
{
}

static char*
search_fields_get_attr(ezxml_t doc, const char* field, const char* attr)
{
}

static void
perform_actions(ezxml_t doc,
                const char* tag, const char* attr,
                int s_attr, int s_tag)
{
  /* Checks its arguments and calls the necessary functions 
     to extract the data. */
  /* DEBUG info */
  printf("DEBUG: %s %s %d %d\n", tag, attr, s_attr, s_tag);
  char* attr_value = NULL;
  char* tag_value = NULL;

  /* get text at named path */
  if (!s_tag && tag != NULL && attr == NULL)
      tag_value = get_text_at_field(doc, tag);
  /* get attribute of the named field path */
  else if (!s_tag && tag != NULL && attr != NULL)
      attr_value = get_attr_at_field(doc, tag, attr);
  /* get all the fields with the name "tag" */
  else if (s_tag && tag != NULL && attr == NULL)
      attr_value = search_fields(doc, tag);
  /* get attribute "attr" from fields named "tag" */
  else if (s_tag && tag != NULL && attr != NULL)
      attr_value = search_fields_get_attr(doc, tag, attr);
  /* get all attributes named "attr" */
  else if (s_attr && attr != NULL)
      attr_value = search_attrs(doc, attr);

  /* DEBUG info */
  if(attr_value != NULL) printf("%s", attr_value);
  if(tag_value != NULL) printf("%s", tag_value);
}


int main(int argc, char* argv[])
{
  /* store attr and tag names */
  char* tag_name = NULL;
  char* attr_name = NULL;

  /* bools to determine whether whe should search for an exact path in 
     the xml, or scan all the fields/tags in order to find one that has
     the required name */
  int search_attr = 0;
  int search_tag  = 0;

  /* parse command line arguments and set variables */
  char c;
  while ((c = getopt(argc, argv, "a:t:A:T:")) != -1)
    {
      switch (c)
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

	default:
	  printf("Invalid use of arguments. Please consult the documentation.");
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

  perform_actions(xml_doc, tag_name, attr_name, search_attr, search_tag);
  printf("%s", doc_file);
  return 0;
}
