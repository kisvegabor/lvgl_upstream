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

typedef struct {
    lv_ll_t parent_ll;
    lv_ll_t style_ll;
    lv_obj_t * view;
} lv_xml_parser_state_t;

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
