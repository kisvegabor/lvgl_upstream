/**
 * @file lv_tabview_xml_parser.h
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
#include "lvgl/lvgl.h"

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

void * lv_tabview_xml_process(lv_obj_t * parent, const char ** attrs);
void * lv_tab_bar_xml_process(lv_obj_t * parent, const char ** attrs);
void * lv_tab_cont_xml_process(lv_obj_t * parent, const char ** attrs);
void * lv_tab_xml_process(lv_obj_t * parent, const char ** attrs);
void * lv_tab_button_xml_process(lv_obj_t * parent, const char ** attrs);


/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_TABVIEW_XML_PARSE_H*/
