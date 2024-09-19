/**
 * @file lv_xml_obj_parser.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "../../lvgl.h"
#include <stdlib.h>

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

void * lv_xml_obj_process(lv_xml_parser_state_t * state, const char ** attrs)
{
    void * item = lv_obj_create(lv_xml_state_get_parent(state));

    lv_obj_xml_apply_attrs(state, item, attrs);

    return item;
}

void lv_obj_xml_apply_attrs(lv_xml_parser_state_t * state, lv_obj_t * obj, const char ** attrs)
{
    for(int i = 0; attrs[i]; i += 2) {
        const char * name = attrs[i];
        const char * value = attrs[i + 1];

        if(lv_streq("x", name)) lv_obj_set_x(obj, atoi(value));
        if(lv_streq("y", name)) lv_obj_set_y(obj, atoi(value));
        if(lv_streq("width", name)) lv_obj_set_width(obj, atoi(value));
        if(lv_streq("height", name)) lv_obj_set_height(obj, atoi(value));
        if(lv_streq("align", name)) lv_obj_set_align(obj, lv_xml_align_text_to_enum_value(value));
        if(lv_streq("styles", name)) lv_xml_styles_add(state, obj, value);
    }
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

