/**
 * @file lv_xml_base_types.h
 *
 */

#ifndef LV_XML_BASE_TYPES_H
#define LV_XML_BASE_TYPES_H

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

lv_state_t lv_xml_state_text_to_enum_value(const char * txt);
lv_part_t lv_xml_part_text_to_enum_value(const char * txt);
lv_align_t lv_xml_align_text_to_enum_value(const char * txt);
lv_base_dir_t lv_xml_dir_text_to_enum_value(const char * txt);
void lv_xml_styles_apply(lv_xml_parser_state_t * state, lv_obj_t * obj, const char * text)

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_XML_BASE_TYPES_H*/
