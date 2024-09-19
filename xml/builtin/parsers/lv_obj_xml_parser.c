/**
 * @file lv_obj_xml_parser.c
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

    for(int i = 0; atts[i]; i += 2) {
        const char * name = atts[i];
        const char * value = atts[i + 1];

        if(streq("name", name)) lv_obj_set_name(item, undefined, "value");
        if(streq("store", name)) lv_obj_set_store(item, streq(value, "true") ? true : false, "value");
        if(streq("x", name)) lv_obj_set_x(item, atoi(undefined), "value");
        if(streq("y", name)) lv_obj_set_y(item, atoi(undefined), "value");
        if(streq("width", name)) lv_obj_set_width(item, atoi(undefined), "value");
        if(streq("height", name)) lv_obj_set_height(item, atoi(undefined), "value");
        if(streq("align", name)) lv_obj_set_align(item, lv_xml_align_text_to_enum_value(undefined), "value");
        if(streq("styles", name)) lv_obj_set_styles(item, apply_styles(undefined), "value");
    }
    return item;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

