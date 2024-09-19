/**
 * @file lv_xml_slider_parser.c
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
static lv_slider_mode_t mode_text_to_enum_value(const char * txt);

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void * lv_xml_slider_process(lv_xml_parser_state_t * state, const char ** attrs)
{
    void * item = lv_slider_create(lv_xml_state_get_parent(state));

    lv_obj_xml_apply_attrs(state, item, attrs); /*Apply the common properties, e.g. width, height, styles flags etc*/

    for(int i = 0; attrs[i]; i += 2) {
        const char * name = attrs[i];
        const char * value = attrs[i + 1];

        //        if(lv_streq("range_min", name)) lv_slider_set_range_min(item, atoi(value));
        //        if(lv_streq("range_max", name)) lv_slider_set_range_max(item, atoi(value));
        if(lv_streq("value", name)) lv_slider_set_value(item, atoi(value), 0);
        if(lv_streq("mode", name)) lv_slider_set_mode(item, mode_text_to_enum_value(value));
    }
    return item;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static lv_slider_mode_t mode_text_to_enum_value(const char * txt)
{
    if(lv_streq("Normal", txt)) return LV_SLIDER_MODE_NORMAL;
    if(lv_streq("Range", txt)) return LV_SLIDER_MODE_RANGE;
    if(lv_streq("Symmetrical", txt)) return LV_SLIDER_MODE_SYMMETRICAL;

    LV_LOG_WARN("%s is an unknown value for slider's mode", txt);
    return 0; /*Return 0 in lack of a better option. */
}
