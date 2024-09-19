/**
 * @file lv_xml_obj_parser.c
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

void * lv_obj_xml_process(lv_obj_t * parent, const char ** attrs)
{
    void * item = lv_obj_create(parent);

    lv_obj_xml_apply_attrs(item, attrs); /*Apply the common properties, e.g. width, height, styles flags etc*/

    for(int i = 0; attrs[i]; i += 2) {
        const char * name = attrs[i];
        const char * value = attrs[i + 1];

        if(streq("x", name)) lv_obj_set_x(item, atoi(value));
        if(streq("y", name)) lv_obj_set_y(item, atoi(value));
        if(streq("width", name)) lv_obj_set_width(item, atoi(value));
        if(streq("height", name)) lv_obj_set_height(item, atoi(value));
        if(streq("align", name)) lv_obj_set_align(item, lv_xml_align_text_to_enum_value(value));
        if(streq("styles", name)) lv_obj_set_styles(item, lv_xml_styles_apply(value));
    }
    return item;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

