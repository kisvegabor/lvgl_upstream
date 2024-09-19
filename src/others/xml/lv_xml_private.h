/**
 * @file lv_xml_ptivate.h
 *
 */

#ifndef LV_XML_PRIVATE_H
#define LV_XML_PRIVATE_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "lv_xml.h"
#include "../../misc/lv_ll.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

typedef struct _lv_xml_parser_state_t {
    lv_ll_t parent_ll;
    lv_ll_t style_ll;
    lv_obj_t * view;
    lv_obj_t * parent;
} lv_xml_parser_state_t;

typedef struct _lv_xml_style_t {
    const char * name;
    lv_style_t style;
} lv_xml_style_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_XML_PRIVATE_H*/
