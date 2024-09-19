/**
 * @file lv_base_xml_parser.c
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
static lv_base_state_t state_text_to_enum_value(const char * txt);
static lv_base_part_t part_text_to_enum_value(const char * txt);
static lv_base_align_t align_text_to_enum_value(const char * txt);
static lv_base_dir_t dir_text_to_enum_value(const char * txt);

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void * lv_base_xml_process(lv_obj_t * parent, const char ** attrs)
{
    void * item = lv_base_create(parent);

    lv_obj_xml_apply_attrs(item, attrs); /*Apply the common properties, e.g. width, height, styles flags etc*/

    for(int i = 0; atts[i]; i += 2) {
        const char * name = atts[i];
        const char * value = atts[i + 1];

        if(streq("state", name)) lv_base_set_state(item, state_text_to_enum_value(undefined), "value");
        if(streq("part", name)) lv_base_set_part(item, part_text_to_enum_value(undefined), "value");
        if(streq("align", name)) lv_base_set_align(item, align_text_to_enum_value(undefined), "value");
        if(streq("dir", name)) lv_base_set_dir(item, dir_text_to_enum_value(undefined), "value");
    }
    return item;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static lv_base_state_t state_text_to_enum_value(const char * txt)
{
    if(streq("default", txt)) return LV_BASE_STATE_DEFAULT;
    if(streq("pressed", txt)) return LV_BASE_STATE_PRESSED;
    if(streq("checked", txt)) return LV_BASE_STATE_CHECKED;

    LV_LOG_WARN("%s is an unknown value for base's state", txt);
    return 0; /*Return 0 in lack of a better option. */
}

static lv_base_part_t part_text_to_enum_value(const char * txt)
{
    if(streq("main", txt)) return LV_BASE_PART_MAIN;
    if(streq("scrollbar", txt)) return LV_BASE_PART_SCROLLBAR;
    if(streq("indicator", txt)) return LV_BASE_PART_INDICATOR;
    if(streq("knob", txt)) return LV_BASE_PART_KNOB;

    LV_LOG_WARN("%s is an unknown value for base's part", txt);
    return 0; /*Return 0 in lack of a better option. */
}

static lv_base_align_t align_text_to_enum_value(const char * txt)
{
    if(streq("top_left", txt)) return LV_BASE_ALIGN_TOP_LEFT;
    if(streq("bottom_right", txt)) return LV_BASE_ALIGN_BOTTOM_RIGHT;
    if(streq("center", txt)) return LV_BASE_ALIGN_CENTER;

    LV_LOG_WARN("%s is an unknown value for base's align", txt);
    return 0; /*Return 0 in lack of a better option. */
}

static lv_base_dir_t dir_text_to_enum_value(const char * txt)
{
    if(streq("top", txt)) return LV_BASE_DIR_TOP;
    if(streq("bottom", txt)) return LV_BASE_DIR_BOTTOM;
    if(streq("left", txt)) return LV_BASE_DIR_LEFT;
    if(streq("right", txt)) return LV_BASE_DIR_RIGHT;

    LV_LOG_WARN("%s is an unknown value for base's dir", txt);
    return 0; /*Return 0 in lack of a better option. */
}