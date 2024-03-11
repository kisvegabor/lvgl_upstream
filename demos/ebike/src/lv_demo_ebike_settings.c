/**
 * @file lv_demo_ebike_settings.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lv_demo_ebike.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static lv_obj_t * left_cont_create(lv_obj_t * parent);
static lv_obj_t * right_cont_create(lv_obj_t * parent);

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lv_demo_ebike_settings_create(void)
{
    lv_obj_t * main_cont = lv_obj_create(lv_screen_active());
    lv_obj_set_style_bg_opa(main_cont, 0, 0);
    lv_obj_set_size(main_cont, lv_pct(100), lv_pct(100));
    lv_obj_set_flex_flow(main_cont, LV_FLEX_FLOW_ROW);

    lv_obj_t * left_cont = left_cont_create(main_cont);
    lv_obj_set_size(left_cont, 164, lv_pct(100));

    lv_obj_t * right_cont = right_cont_create(main_cont);
    lv_obj_set_size(right_cont, lv_pct(100), lv_pct(100));
    lv_obj_set_flex_grow(right_cont, 1);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/


static lv_obj_t * left_cont_create(lv_obj_t * parent)
{
    lv_obj_t * left_cont = lv_obj_create(parent);
    lv_obj_set_style_bg_opa(left_cont, 0, 0);
    lv_obj_remove_flag(left_cont, LV_OBJ_FLAG_SCROLLABLE);

    LV_FONT_DECLARE(font_ebike_19);
    lv_obj_t * label = lv_label_create(left_cont);
    lv_obj_align(label, LV_ALIGN_TOP_LEFT, 24, 16);
    lv_label_set_text(label, "SETTINGS");
    lv_obj_set_style_text_font(label, &font_ebike_19, 0);

    LV_IMAGE_DECLARE(img_ebike_settings_large);
    lv_obj_t * scale = lv_image_create(left_cont);
    lv_image_set_src(scale, &img_ebike_settings_large);
    lv_obj_align(scale, LV_ALIGN_BOTTOM_MID, 0, 0);

    return left_cont;
}


static lv_obj_t * slider_create(lv_obj_t * parent, const char * title, const char * desc)
{
    LV_FONT_DECLARE(font_ebike_19);
    lv_obj_t * main_cont = lv_obj_create(parent);
    lv_obj_set_size(main_cont, lv_pct(100), LV_SIZE_CONTENT);
    lv_obj_set_style_bg_opa(main_cont, 0, 0);
    lv_obj_set_flex_flow(main_cont, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_style_text_font(main_cont, &font_ebike_19, 0);
    lv_obj_set_style_pad_all(main_cont, 10, 0);
    lv_obj_set_style_pad_column(main_cont, 4, 0);

    lv_obj_t * label;
    label = lv_label_create(main_cont);
    lv_label_set_text(label, title);
    lv_obj_set_width(label, lv_pct(100));

    label = lv_label_create(main_cont);
    lv_label_set_text(label, desc);
    lv_obj_set_width(label, lv_pct(100));

    lv_obj_t * slider = lv_slider_create(main_cont);
    lv_obj_set_size(slider, lv_pct(100), 4);
    lv_obj_set_ext_click_area(slider, 16);
    lv_obj_set_style_bg_opa(slider, LV_OPA_40, 0);
    lv_obj_set_style_radius(slider, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_style_bg_color(slider, EBIKE_COLOR_TURQUOISE, 0);
    lv_obj_set_style_bg_color(slider, EBIKE_COLOR_TURQUOISE, LV_PART_INDICATOR);
    lv_obj_set_style_radius(slider, LV_RADIUS_CIRCLE, LV_PART_INDICATOR);
    lv_obj_set_style_pad_all(slider, 8, LV_PART_KNOB);
    lv_obj_set_style_radius(slider, LV_RADIUS_CIRCLE, LV_PART_KNOB);
    lv_obj_set_style_border_width(slider, 4, LV_PART_KNOB);
    lv_obj_set_style_border_color(slider, EBIKE_COLOR_TURQUOISE, LV_PART_KNOB);
    lv_obj_set_style_bg_color(slider, lv_color_black(), LV_PART_KNOB);
    lv_obj_set_style_margin_top(slider, 12, 0);
    return main_cont;
}

static lv_obj_t * switch_create(lv_obj_t * parent, const char * title, const char * value1, const char * value2)
{
    LV_FONT_DECLARE(font_ebike_19);
    lv_obj_t * main_cont = lv_obj_create(parent);
    lv_obj_set_size(main_cont, lv_pct(100), LV_SIZE_CONTENT);
    lv_obj_set_style_bg_opa(main_cont, 0, 0);
    lv_obj_set_flex_flow(main_cont, LV_FLEX_FLOW_ROW);
    lv_obj_set_style_flex_main_place(main_cont, LV_FLEX_ALIGN_SPACE_BETWEEN, 0);
    lv_obj_set_style_text_font(main_cont, &font_ebike_19, 0);
    lv_obj_set_style_pad_all(main_cont, 10, 0);
    lv_obj_set_style_pad_column(main_cont, 4, 0);

    lv_obj_t * label;
    label = lv_label_create(main_cont);
    lv_label_set_text(label, title);
    lv_obj_set_width(label, lv_pct(100));

    lv_obj_t * sw_bg = lv_obj_create(main_cont);
    lv_obj_set_size(sw_bg, 80, 24);
    lv_obj_set_ext_click_area(sw_bg, 16);
    lv_obj_set_style_radius(sw_bg, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_style_bg_color(sw_bg, EBIKE_COLOR_TURQUOISE, 0);

    lv_obj_t * sw_knob = lv_obj_create(sw_bg);
    lv_obj_set_size(sw_knob, 36, 18);
    lv_obj_align(sw_knob, LV_ALIGN_LEFT_MID, 3, 0);
    lv_obj_set_ext_click_area(sw_knob, 16);
    lv_obj_set_style_radius(sw_knob, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_style_bg_color(sw_knob, lv_color_black(), 0);
    lv_obj_set_style_outline_width(sw_knob, 1, 0);
    lv_obj_set_style_outline_opa(sw_knob, 100, 0);
    lv_obj_remove_flag(sw_knob, LV_OBJ_FLAG_SCROLLABLE);

    label = lv_label_create(sw_knob);
    lv_label_set_text(label, value1);
    lv_obj_center(label);

    return main_cont;
}


static lv_obj_t * right_cont_create(lv_obj_t * parent)
{
    lv_obj_t * right_cont = lv_obj_create(parent);
    lv_obj_set_style_bg_opa(right_cont, 0, 0);
    lv_obj_set_flex_flow(right_cont, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_style_pad_ver(right_cont, 12, 0);
    lv_obj_set_style_pad_right(right_cont, 8, 0);
    lv_obj_set_style_pad_gap(right_cont, 8, 0);

    switch_create(right_cont, "Title", "v1", "v2");
    slider_create(right_cont, "Title", "Desc");
    slider_create(right_cont, "Title", "Desc");
    slider_create(right_cont, "Title", "Desc");
    slider_create(right_cont, "Title", "Desc");
    slider_create(right_cont, "Title", "Desc");
    slider_create(right_cont, "Title", "Desc");
    slider_create(right_cont, "Title", "Desc");
    slider_create(right_cont, "Title", "Desc");
    slider_create(right_cont, "Title", "Desc");

    return right_cont;
}
