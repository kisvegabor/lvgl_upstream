/**
 * @file lv_label_xml_parser.h
 *
 */

#ifndef LV_LABEL_XML_PARSER_H
#define LV_LABEL_XML_PARSER_H

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

void * lv_label_xml_process(lv_obj_t * parent, const char ** attrs);


/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_LABEL_XML_PARSE_H*/
