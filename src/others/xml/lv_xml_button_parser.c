/**
 * @file lv_xml_button_parser.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "../../lvgl.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void * lv_xml_button_process(lv_xml_parser_state_t * state, const char ** attrs)
{
    void * item = lv_button_create(lv_xml_state_get_parent(state));

    lv_obj_xml_apply_attrs(state, item, attrs); /*Apply the common properties, e.g. width, height, styles flags etc*/

    for(int i = 0; attrs[i]; i += 2) {
        const char * name = attrs[i];
        const char * value = attrs[i + 1];

    }
    return item;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

