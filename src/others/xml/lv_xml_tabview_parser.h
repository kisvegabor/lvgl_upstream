/**
 * @file lv_xml_tabview_parser.h
 *
 */

#ifndef LV_TABVIEW_XML_PARSER_H
#define LV_TABVIEW_XML_PARSER_H

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

void * lv_xml_tabview_process(lv_xml_parser_state_t * state, const char ** attrs);
void * lv_xml_tabview_tab_bar_process(lv_xml_parser_state_t * state, const char ** attrs);
void * lv_xml_tabview_tab_process(lv_xml_parser_state_t * state, const char ** attrs);


/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_TABVIEW_XML_PARSE_H*/
