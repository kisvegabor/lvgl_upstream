/**
 * @file lv_demo_ebike_stat.c
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

void lv_demo_ebike_stat_create(void)
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
    lv_label_set_text(label, "STATS");
    lv_obj_set_style_text_font(label, &font_ebike_19, 0);

    LV_IMAGE_DECLARE(img_ebike_stat_large);
    lv_obj_t * scale = lv_image_create(left_cont);
    lv_image_set_src(scale, &img_ebike_stat_large);
    lv_obj_align(scale, LV_ALIGN_BOTTOM_MID, 0, 0);

    return left_cont;
}

static lv_obj_t * right_cont_create(lv_obj_t * parent)
{

    lv_obj_t * right_cont = lv_obj_create(parent);
    lv_obj_set_style_bg_opa(right_cont, 0, 0);
    lv_obj_set_flex_flow(right_cont, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_style_pad_ver(right_cont, 12, 0);
    lv_obj_set_style_pad_right(right_cont, 8, 0);
    lv_obj_set_style_pad_gap(right_cont, 8, 0);

    lv_obj_t * tab_cont = lv_obj_create(right_cont);
    lv_obj_set_style_bg_opa(tab_cont, 100, 0);
    lv_obj_set_size(tab_cont, lv_pct(100), 21);

    lv_button_create(tab_cont);

    lv_obj_t * date_cont = lv_obj_create(right_cont);
    lv_obj_set_style_bg_opa(date_cont, 70, 0);
    lv_obj_set_size(date_cont, lv_pct(100), 42);

    lv_obj_t * chart = lv_chart_create(right_cont);
    lv_obj_set_style_bg_opa(chart, 100, 0);
    lv_obj_set_flex_grow(chart, 1);
    lv_obj_set_width(chart, lv_pct(100));
    lv_chart_set_point_count(chart, 9);
    lv_obj_set_style_line_width(chart, 3, LV_PART_ITEMS);
    lv_obj_set_style_size(chart, 10, 10, LV_PART_INDICATOR);
    lv_obj_set_style_bg_opa(chart, LV_OPA_COVER, LV_PART_INDICATOR);
    lv_obj_set_style_bg_color(chart, lv_color_black(), LV_PART_INDICATOR);
    lv_obj_set_style_radius(chart, LV_RADIUS_CIRCLE, LV_PART_INDICATOR);
    lv_obj_set_style_border_color(chart, lv_color_black(), LV_PART_INDICATOR);
    lv_obj_set_style_border_width(chart, 2, LV_PART_INDICATOR);

    lv_chart_series_t * ser = lv_chart_add_series(chart, lv_color_white(), 0);
    lv_chart_set_next_value(chart, ser, 30);
    lv_chart_set_next_value(chart, ser, 60);
    lv_chart_set_next_value(chart, ser, 22);
    lv_chart_set_next_value(chart, ser, 40);
    lv_chart_set_next_value(chart, ser, 48);
    lv_chart_set_next_value(chart, ser, 30);
    lv_chart_set_next_value(chart, ser, 69);
    lv_chart_set_next_value(chart, ser, 21);
    lv_chart_set_next_value(chart, ser, 60);

    lv_obj_t * stat_cont = lv_obj_create(right_cont);
    lv_obj_set_style_bg_opa(stat_cont, 70, 0);
    lv_obj_set_size(stat_cont, lv_pct(100), 36);

    return right_cont;
}
