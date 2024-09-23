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
#include "../../misc/lv_types.h"
#include "../../misc/lv_area.h"

/**********************
 *      TYPEDEFS
 **********************/
typedef struct _lv_xml_parser_state_t lv_xml_parser_state_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

lv_state_t lv_xml_state_string_to_enum_value(const char * txt);
lv_part_t lv_xml_part_string_to_enum_value(const char * txt);
lv_align_t lv_xml_align_string_to_enum_value(const char * txt);
lv_dir_t lv_xml_dir_string_to_enum_value(const char * txt);
void lv_xml_styles_add(lv_xml_parser_state_t * state, lv_obj_t * obj, const char * text);
void lv_xml_style_process(lv_xml_parser_state_t * state, const char ** attrs);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_XML_BASE_TYPES_H*/
