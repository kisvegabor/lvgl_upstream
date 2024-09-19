/**
 * @file lv_button_xml_parser.h
 *
 */

#ifndef LV_BUTTON_XML_PARSER_H
#define LV_BUTTON_XML_PARSER_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "lvgl/lvgl.h"

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

void * lv_button_xml_process(lv_obj_t * parent, const char ** attrs);


/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_BUTTON_XML_PARSE_H*/
