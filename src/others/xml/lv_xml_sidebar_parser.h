/**
 * @file lv_xml_sidebar_parser.h
 *
 */

#ifndef LV_SIDEBAR_XML_PARSER_H
#define LV_SIDEBAR_XML_PARSER_H

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

void * lv_sidebar_xml_process(lv_obj_t * parent, const char ** attrs);


/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_SIDEBAR_XML_PARSE_H*/
