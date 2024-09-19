/**
 * @file lv_button_xml_parser.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lvgl/lvgl"

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

void * lv_button_xml_process(lv_obj_t * parent, const char ** attrs)
{
    void * item = lv_button_create(parent);

    lv_obj_xml_apply_attrs(item, attrs); /*Apply the common properties, e.g. width, height, styles flags etc*/

    for(int i = 0; atts[i]; i += 2) {
        const char * name = atts[i];
        const char * value = atts[i + 1];

    }
    return item;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

