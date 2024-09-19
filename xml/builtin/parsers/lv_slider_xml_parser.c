/**
 * @file lv_slider_xml_parser.c
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
static lv_slider_orientation_t orientation_text_to_enum_value(const char * txt);

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

    for(int i = 0; atts[i]; i += 2) {
        const char * name = atts[i];
        const char * value = atts[i + 1];

        if(streq("range_min", name)) lv_slider_set_range_min(item, atoi(undefined), "value");
        if(streq("range_max", name)) lv_slider_set_range_max(item, atoi(undefined), "value");
        if(streq("value", name)) lv_slider_set_value(item, atoi(undefined), "value");
        if(streq("mode", name)) lv_slider_set_mode(item, mode_text_to_enum_value(undefined), "value");
        if(streq("orientation", name)) lv_slider_set_orientation(item, orientation_text_to_enum_value(undefined), "value");
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
static lv_slider_orientation_t orientation_text_to_enum_value(const char * txt)
{
    if(streq("auto", txt)) return LV_SLIDER_ORIENTATION_AUTO;
    if(streq("horizontal", txt)) return LV_SLIDER_ORIENTATION_HORIZONTAL;
    if(streq("vertical", txt)) return LV_SLIDER_ORIENTATION_VERTICAL;

    LV_LOG_WARN("%s is an unknown value for slider's orientation", txt);
    return 0; /*Return 0 in lack of a better option. */
}
