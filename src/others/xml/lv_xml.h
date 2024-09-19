/**
 * @file lv_xml.h
 *
 */

#ifndef LV_XML_H
#define LV_XML_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "../../misc/lv_types.h"
#include "lv_xml_base_types.h"
#include "lv_xml_obj_parser.h"

/*********************
 *      DEFINES
 *********************/

//HACK!!!
#define LV_LABEL_LONG_MODE_SCROLL LV_LABEL_LONG_SCROLL
#define LV_LABEL_LONG_MODE_WRAP LV_LABEL_LONG_WRAP

/**********************
 *      TYPEDEFS
 **********************/

typedef  void * (*lv_xml_widget_process_cb_t)(lv_xml_parser_state_t * state, const char ** attrs);

/**********************
 * GLOBAL PROTOTYPES
 **********************/

lv_result_t lv_xml_register_processor(const char * name, lv_xml_widget_process_cb_t cb);
lv_result_t lv_xml_load_data(lv_obj_t * parent, const char * data, size_t data_len);
lv_result_t lv_xml_load_file(lv_obj_t * parent, const char * path);
const char * lv_xml_get_value_of(const char ** attrs, const char * name);
void * lv_xml_state_get_parent(lv_xml_parser_state_t * state);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_XML_H*/
