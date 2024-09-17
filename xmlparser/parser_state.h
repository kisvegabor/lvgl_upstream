#ifndef PARSER_STATE_H
#define PARSER_STATE_H

#include "lvgl/lvgl.h"
#include "../libexpat/expat.h"
#include <string.h>
#include "lvgl/src/lvgl_private.h"
/**
 * Structure to hold the parser state
 */
typedef struct {
	lv_ll_t parent_ll;
} ParserState;


void start_element_handler(void *userData, const char *name, const char **atts);

void end_element_handler(void *userData, const char *name);

void character_data_handler(void *userData, const char *s, int len);

#endif // PARSER_STATE_H
