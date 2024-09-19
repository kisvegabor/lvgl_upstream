/**
 * @file lv_xml_label_parser.c
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
static lv_label_long_mode_t long_mode_text_to_enum_value(const char * txt);

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void * lv_xml_label_process(lv_xml_parser_state_t * state, const char ** attrs)
{
    void * item = lv_label_create(lv_xml_state_get_parent(state));

    lv_obj_xml_apply_attrs(state, item, attrs); /*Apply the common properties, e.g. width, height, styles flags etc*/

    for(int i = 0; attrs[i]; i += 2) {
        const char * name = attrs[i];
        const char * value = attrs[i + 1];

        if(lv_streq("text", name)) lv_label_set_text(item, value);
        if(lv_streq("long_mode", name)) lv_label_set_long_mode(item, long_mode_text_to_enum_value(value));
    }
    return item;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static lv_label_long_mode_t long_mode_text_to_enum_value(const char * txt)
{
    if(lv_streq("wrap", txt)) return LV_LABEL_LONG_MODE_WRAP;
    if(lv_streq("scroll", txt)) return LV_LABEL_LONG_MODE_SCROLL;

    LV_LOG_WARN("%s is an unknown value for label's long_mode", txt);
    return 0; /*Return 0 in lack of a better option. */
}
