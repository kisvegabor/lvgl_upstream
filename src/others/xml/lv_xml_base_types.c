/**
 * @file lv_xml_base_parser.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lv_xml.h"
#include "../../../lvgl.h"
#include "../../../src/lvgl_private.h"
#include <string.h>
#include <stdlib.h>

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static int32_t part_text_to_enum_value_core(const char * txt);
static int32_t state_text_to_enum_value_core(const char * txt);
static lv_style_t * get_style_by_name(lv_xml_parser_state_t * state, const char * name);

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

lv_state_t lv_xml_state_text_to_enum_value(const char * txt)
{
    int32_t state = state_text_to_enum_value_core(txt);
    if(state >= 0)  return (lv_state_t)state;

    LV_LOG_WARN("%s is an unknown value for base's state", txt);
    return 0; /*Return 0 in lack of a better option. */
}

lv_part_t lv_xml_part_text_to_enum_value(const char * txt)
{
    int32_t part = part_text_to_enum_value_core(txt);
    if(part >= 0)  return part;

    LV_LOG_WARN("%s is an unknown value for base's part", txt);
    return 0; /*Return 0 in lack of a better option. */
}

lv_align_t lv_xml_align_text_to_enum_value(const char * txt)
{
    if(lv_streq("top_left", txt)) return LV_ALIGN_TOP_LEFT;
    if(lv_streq("bottom_right", txt)) return LV_ALIGN_BOTTOM_RIGHT;
    if(lv_streq("center", txt)) return LV_ALIGN_CENTER;

    LV_LOG_WARN("%s is an unknown value for base's align", txt);
    return 0; /*Return 0 in lack of a better option. */
}

lv_dir_t lv_xml_dir_text_to_enum_value(const char * txt)
{
    if(lv_streq("top", txt)) return LV_DIR_TOP;
    if(lv_streq("bottom", txt)) return LV_DIR_BOTTOM;
    if(lv_streq("left", txt)) return LV_DIR_LEFT;
    if(lv_streq("right", txt)) return LV_DIR_RIGHT;

    LV_LOG_WARN("%s is an unknown value for base's dir", txt);
    return 0; /*Return 0 in lack of a better option. */
}

void lv_xml_style_process(lv_xml_parser_state_t * state, const char ** attrs)
{
    const char * style_name =  lv_xml_get_value_of(attrs, "name");
    lv_xml_style_t * xml_style = lv_ll_ins_tail(&state->style_ll);
    lv_style_t * style = &xml_style->style;
    lv_style_init(style);
    xml_style->name = lv_strdup(style_name);

    for(int i = 0; attrs[i]; i += 2) {
        const char * name = attrs[i];
        const char * value = attrs[i + 1];
        if(lv_streq(name, "name")) continue;
        if(lv_streq(name, "help")) continue;
        if(lv_streq(name, "bg_color")) lv_style_set_bg_color(style, lv_color_hex(strtol(value, NULL, 16)));
        else {
            LV_LOG_WARN("%s style property is not supported", name);
        }
    }
}

void lv_xml_styles_add(lv_xml_parser_state_t * state, lv_obj_t * obj, const char * text)
{
    // Duplicate the input text to avoid modifying the original string
    char * str = lv_strdup(text);

    uint32_t selector = 0; // This will hold the selector for state and part
    char * style_name = NULL;

    // Split the string based on space and colons
    char * onestyle_state = NULL;
    char * onestyle_str = strtok_r(str, " ", &onestyle_state);
    while(onestyle_str != NULL) {
        // Parse the parts and states after the space
        char * selector_state = NULL;
        style_name = strtok_r(onestyle_str, ":", &selector_state);
        char * selector_str = strtok_r(NULL, ":", &selector_state);
        while(selector_str != NULL) {
            // Handle different states and parts
            selector |= state_text_to_enum_value_core(selector_str);
            selector |= part_text_to_enum_value_core(selector_str);

            // Move to the next token
            selector_str = strtok_r(NULL, ":", &selector_state);
        }

        // Apply the selector-based style if valid
        if(style_name != NULL) {
            lv_style_t * style = get_style_by_name(state, style_name);
            if(style) {
                lv_obj_add_style(obj, style, selector); // Apply with the built selector
            }
        }
        onestyle_str = strtok_r(NULL, " ", &onestyle_state);
    }

    lv_free(str);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static int32_t part_text_to_enum_value_core(const char * txt)
{
    if(lv_streq("main", txt)) return LV_PART_MAIN;
    if(lv_streq("scrollbar", txt)) return LV_PART_SCROLLBAR;
    if(lv_streq("indicator", txt)) return LV_PART_INDICATOR;
    if(lv_streq("knob", txt)) return LV_PART_KNOB;

    return -1;
}

static int32_t state_text_to_enum_value_core(const char * txt)
{
    if(lv_streq("default", txt)) return LV_STATE_DEFAULT;
    if(lv_streq("pressed", txt)) return LV_STATE_PRESSED;
    if(lv_streq("checked", txt)) return LV_STATE_CHECKED;

    return -1;
}

static lv_style_t * get_style_by_name(lv_xml_parser_state_t * state, const char * name)
{
    lv_xml_style_t * xml_style;
    LV_LL_READ(&state->style_ll, xml_style) {
        if(lv_streq(xml_style->name, name)) return &xml_style->style;
    }

    LV_LOG_WARN("No style found with %s name", name);

    return NULL;
}

