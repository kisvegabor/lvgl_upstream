/**
 * @file lv_xml_tabview_parser.c
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

void * lv_tabview_xml_process(lv_obj_t * parent, const char ** attrs)
{
    void * item = lv_tabview_create(parent);

    lv_obj_xml_apply_attrs(item, attrs); /*Apply the common properties, e.g. width, height, styles flags etc*/

    for(int i = 0; attrs[i]; i += 2) {
        const char * name = attrs[i];
        const char * value = attrs[i + 1];

        if(streq("act_tab", name)) lv_tabview_set_act_tab(item, atoi(value));
    }
    return item;
}

void * lv_tab_bar_xml_parse_create(lv_obj_t * parent, const char ** attrs)
{
    void * item = lv_tabview_get_tab_bar(parent);

    lv_obj_xml_apply_attrs(item, attrs); /*Apply the common properties, e.g. width, height, styles flags etc*/

    for(int i = 0; attrs[i]; i += 2) {
        const char * name = attrs[i];
        const char * value = attrs[i + 1];

        if(streq("position", name)) lv_tabview_set_tab_bar_position(item, lv_xml_dir_align_text_to_enum_value(value));
    }

    return item;
}

void * lv_tab_cont_xml_parse_create(lv_obj_t * parent, const char ** attrs)
{
    void * item = lv_tabview_get_tab_cont(parent);

    lv_obj_xml_apply_attrs(item, attrs); /*Apply the common properties, e.g. width, height, styles flags etc*/

    /* There are no properties to process */

    return item;
}

void * lv_tab_xml_parse_create(lv_obj_t * parent, const char ** attrs)
{
    const char * text = lv_xml_get_value_of(attrs, "text")
                        const char * pos = lv_xml_get_value_of(attrs, "pos")
                                           void * item = lv_tabview_add_tab(parent, text, atoi(pos));

    lv_obj_xml_apply_attrs(item, attrs); /*Apply the common properties, e.g. width, height, styles flags etc*/

    /* There are no properties to process */

    return item;
}

void * lv_tab_button_xml_parse_create(lv_obj_t * parent, const char ** attrs)
{
    const char * index_str = lv_xml_get_value_of(attrs, "index");
    void * item = lv_tabview_get_tab_button(parent, atoi(index_str));

    lv_obj_xml_apply_attrs(item, attrs); /*Apply the common properties, e.g. width, height, styles flags etc*/

    /* There are no properties to process */

    return item;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

