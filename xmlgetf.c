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

static const char* 
get_attribute_at_field(ezxml_t* doc, const char* field, const char* attr)
{
}

static const char*
get_text_at_field(ezxml_t* doc, const char* field)
{
}

static const char*
search_attribute(ezxml_t* doc, const char *attr)
{
}

static const char*
search_field(ezxml_t* doc, const char *attr)
{
}

static void
perform_actions(const char* tag, const char* attr, int s_attr, int s_tag)
{
}


int main(int argc, char* argv[])
{

  /* store attribute and tag names */
  const char* tag_name;
  const char* attr_name;

  /* bools to determine whether whe should search for an exact path in 
     the xml, or scan all the fields/tags in order to find one that has
     the required name */
  int search_attr = 0;
  int search_tag  = 0;

  /* get target file and parse xml document*/
  const char* doc_file = argv[argc-1];
  ezxml_t xml_doc = ezxml_parse_file(doc_file);
  /* parse command line arguments and do required actions */
  char c;
  while ((c = getopt(argc, argv, "atAT")) != -1)
    {
      switch (c)
	{
	case 'a':
	  break;

	case 't':
	  break;

	case 'A':
	  search_attr = 1;
	  break;

	case 'T':
	  search_tag = 1;
	  break;

	default:
	  printf("Invalid use of arguments. Please consult the documentation.");
	  break;
	}
    }
  perform_actions(tag_name, attr_name, search_attr, search_tag);
  printf("%s", doc_file);
  return 0;
}
