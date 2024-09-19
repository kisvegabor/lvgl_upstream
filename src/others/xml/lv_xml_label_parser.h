/**
 * @file lv_xml_label_parser.h
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
#include "lv_xml.h"

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

void * lv_xml_label_process(lv_xml_parser_state_t * state, const char ** attrs);


/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_LABEL_XML_PARSE_H*/
