/**
 * @file lv_xml_label_parser.c
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

void * lv_label_xml_process(lv_obj_t * parent, const char ** attrs)
{
    void * item = lv_label_create(parent);

    lv_obj_xml_apply_attrs(item, attrs); /*Apply the common properties, e.g. width, height, styles flags etc*/

    for(int i = 0; attrs[i]; i += 2) {
        const char * name = attrs[i];
        const char * value = attrs[i + 1];

        if(streq("text", name)) lv_label_set_text(item, value);
        if(streq("long_mode", name)) lv_label_set_long_mode(item, long_mode_text_to_enum_value(value));
    }
    return item;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static lv_label_long_mode_t long_mode_text_to_enum_value(const char * txt)
{
    if(streq("wrap", txt)) return LV_LABEL_LONG_MODE_WRAP;
    if(streq("scroll", txt)) return LV_LABEL_LONG_MODE_SCROLL;

    LV_LOG_WARN("%s is an unknown value for label's long_mode", txt);
    return 0; /*Return 0 in lack of a better option. */
}
