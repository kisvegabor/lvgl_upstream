#include "xml_parser.h"
#include "lvgl/libexpat/expat.h"
#include "parser_state.h"
#include "lvgl/lvgl.h"
#include <dirent.h>
#include <stdio.h>

int xml_parse(const char *data)
{
  lv_obj_clean(lv_scr_act());

  // Initialize the parser state
  ParserState state = {};
  lv_ll_init(&state.parent_ll, sizeof(lv_obj_t*));

  // Create an XML parser and set handlers
  XML_Parser parser = XML_ParserCreate(NULL);
  XML_SetUserData(parser, &state);
  XML_SetElementHandler(parser, start_element_handler, end_element_handler);
  XML_SetCharacterDataHandler(parser, character_data_handler);

  // Parse the XML
  if (XML_Parse(parser, data, strlen(data), XML_TRUE) == XML_STATUS_ERROR) {
      fprintf(stderr, "lved-runtime: Parse error: %s\n", XML_ErrorString(XML_GetErrorCode(parser)));
      XML_ParserFree(parser);
      return 1;
  }

  XML_ParserFree(parser);


  return 0;

}
