/**
 * @file lv_xml_slider_parser.c
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

void * lv_slider_xml_process(lv_obj_t * parent, const char ** attrs)
{
    void * item = lv_slider_create(parent);

    lv_obj_xml_apply_attrs(item, attrs); /*Apply the common properties, e.g. width, height, styles flags etc*/

    for(int i = 0; attrs[i]; i += 2) {
        const char * name = attrs[i];
        const char * value = attrs[i + 1];

        if(streq("range_min", name)) lv_slider_set_range_min(item, atoi(value));
        if(streq("range_max", name)) lv_slider_set_range_max(item, atoi(value));
        if(streq("value", name)) lv_slider_set_value(item, atoi(value));
        if(streq("mode", name)) lv_slider_set_mode(item, mode_text_to_enum_value(value));
    }
    return item;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static lv_slider_mode_t mode_text_to_enum_value(const char * txt)
{
    if(streq("Normal", txt)) return LV_SLIDER_MODE_NORMAL;
    if(streq("Range", txt)) return LV_SLIDER_MODE_RANGE;
    if(streq("Symmetrical", txt)) return LV_SLIDER_MODE_SYMMETRICAL;

    LV_LOG_WARN("%s is an unknown value for slider's mode", txt);
    return 0; /*Return 0 in lack of a better option. */
}
