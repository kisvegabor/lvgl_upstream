/**
 * @file lv_xml_tabview_parser.c
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

void * lv_xml_tabview_process(lv_xml_parser_state_t * state, const char ** attrs)
{
    void * item = lv_tabview_create(lv_xml_state_get_parent(state));

    lv_obj_xml_apply_attrs(state, item, attrs); /*Apply the common properties, e.g. width, height, styles flags etc*/

    for(int i = 0; attrs[i]; i += 2) {
        const char * name = attrs[i];
        const char * value = attrs[i + 1];

        if(lv_streq("active", name)) lv_tabview_set_active(item, atoi(value), 0);
    }
    return item;
}

void * lv_xml_tabview_tab_bar_process(lv_xml_parser_state_t * state, const char ** attrs)
{
    void * item = lv_tabview_get_tab_bar(lv_xml_state_get_parent(state));

    lv_obj_xml_apply_attrs(state, item, attrs); /*Apply the common properties, e.g. width, height, styles flags etc*/

    for(int i = 0; attrs[i]; i += 2) {
        const char * name = attrs[i];
        const char * value = attrs[i + 1];

        if(lv_streq("position", name)) lv_tabview_set_tab_bar_position(item, lv_xml_dir_text_to_enum_value(value));
    }

    return item;
}

void * lv_xml_tabview_tab_process(lv_xml_parser_state_t * state, const char ** attrs)
{
    const char * text = lv_xml_get_value_of(attrs, "text");
    void * item = lv_tabview_add_tab(lv_xml_state_get_parent(state), text);

    lv_obj_xml_apply_attrs(state, item, attrs); /*Apply the common properties, e.g. width, height, styles flags etc*/

    /* There are no properties to process */

    return item;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

