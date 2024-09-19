/**
 * @file lv_xml_obj_parser.h
 *
 */

#ifndef LV_OBJ_XML_PARSER_H
#define LV_OBJ_XML_PARSER_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "lv_xml.h"

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

void * lv_xml_obj_process(lv_xml_parser_state_t * state, const char ** attrs);
void lv_obj_xml_apply_attrs(lv_xml_parser_state_t * state, lv_obj_t * obj, const char ** attrs);


/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_OBJ_XML_PARSE_H*/
