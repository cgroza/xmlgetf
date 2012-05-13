#include <stdio.h>
#include "ezxml/ezxml.h"

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


int main(int argc, char* argv[])
{
  /* get target file and parse xml document*/
  const char* doc_file = argv[argc-1];
  ezxml_t xml_doc = ezxml_parse_file(doc_file);
  printf("%d", doc_file);
  return 0;
}
