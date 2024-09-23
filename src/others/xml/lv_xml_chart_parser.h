/**
 * @file lv_xml_chart_parser.h
 *
 */

#ifndef LV_CHART_XML_PARSER_H
#define LV_CHART_XML_PARSER_H

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

void * lv_xml_chart_process(lv_xml_parser_state_t * state, const char ** attrs);
void * lv_xml_chart_series_process(lv_xml_parser_state_t * state, const char ** attrs);
void * lv_xml_chart_cursor_process(lv_xml_parser_state_t * state, const char ** attrs);


/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_CHART_XML_PARSE_H*/
