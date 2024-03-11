/**
 * @file lv_demo_ebike_home.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lv_demo_ebike.h"

/*********************
 *      DEFINES
 *********************/
#define EBIKE_COLOR_TURQUOISE lv_color_hex(0x55FFEB)
#define EBIKE_COLOR_LIME lv_color_hex(0x91FF3B)

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static lv_obj_t * left_cont_create(lv_obj_t * parent);
static lv_obj_t * right_cont_create(lv_obj_t * parent);
static lv_obj_t * roller_create(lv_obj_t * parent, const char * opts, lv_roller_mode_t mode);
static lv_obj_t * card_labels_create(lv_obj_t * parent, const char * value, const char * unit, const char * title);

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lv_demo_ebike_home_create(void)
{

    lv_obj_t * main_cont = lv_obj_create(lv_screen_active());
    lv_obj_set_style_bg_opa(main_cont, 0, 0);
    lv_obj_set_size(main_cont, lv_pct(100), lv_pct(100));
    lv_obj_set_flex_flow(main_cont, LV_FLEX_FLOW_ROW);

    lv_obj_t * left_cont = left_cont_create(main_cont);
    lv_obj_set_size(left_cont, 264, lv_pct(100));

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

    LV_IMAGE_DECLARE(img_ebike_scale);
    lv_obj_t * scale = lv_image_create(left_cont);
    lv_image_set_src(scale, &img_ebike_scale);
    lv_obj_align(scale, LV_ALIGN_LEFT_MID, 0, 0);

    lv_obj_t * arc = lv_arc_create(left_cont);
    lv_obj_set_size(arc, 440, 440);
    lv_obj_align(arc, LV_ALIGN_LEFT_MID, 52, 0);
    lv_obj_set_style_arc_width(arc, 20, 0);
    lv_obj_set_style_arc_width(arc, 20, LV_PART_INDICATOR);
    lv_obj_set_style_bg_opa(arc, LV_OPA_0, LV_PART_KNOB);
    lv_obj_set_style_arc_opa(arc, LV_OPA_0, 0);
    lv_obj_set_style_arc_color(arc, EBIKE_COLOR_TURQUOISE, LV_PART_INDICATOR);

    uint32_t i;
    for(i = 0; i < 5; i++) {
        LV_FONT_DECLARE(font_ebike_19);
        lv_obj_t * obj = lv_obj_create(left_cont);
        lv_obj_set_style_bg_color(obj, lv_color_black(), 0);
        lv_obj_set_style_bg_opa(obj, LV_OPA_0, 0);
        lv_obj_set_size(obj, 45, 40);
        lv_obj_align(obj, LV_ALIGN_LEFT_MID, -10, 0);
        lv_obj_set_style_transform_pivot_x(obj, 260, 0);
        lv_obj_set_style_transform_pivot_y(obj, lv_pct(50), 0);
        lv_obj_set_style_transform_rotation(obj, -260 + i * 150, 0);

        lv_obj_t * label = lv_label_create(obj);
        lv_obj_align(label, LV_ALIGN_RIGHT_MID, 0, 0);
        lv_label_set_text_fmt(label, "%d", (i + 1) * 20);
        lv_obj_set_style_text_font(label, &font_ebike_19, 0);
        lv_obj_set_style_transform_pivot_x(label, lv_pct(100), 0);
        lv_obj_set_style_transform_pivot_y(label, lv_pct(50), 0);

        if(i == 2) {
            lv_obj_set_style_transform_scale(label, 512, 0);
        }
    }

    lv_obj_t * dashboard_center_cont = lv_obj_create(left_cont);
    lv_obj_set_style_bg_opa(dashboard_center_cont, 0, 0);
    lv_obj_align(dashboard_center_cont, LV_ALIGN_LEFT_MID, 110, 0);
    lv_obj_set_size(dashboard_center_cont, 145, 240);

    lv_obj_t * top_cont = lv_obj_create(dashboard_center_cont);
    lv_obj_set_style_bg_opa(top_cont, 0, 0);
    lv_obj_set_size(top_cont, lv_pct(100), LV_SIZE_CONTENT);
    lv_obj_set_flex_flow(top_cont, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(top_cont, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    LV_IMAGE_DECLARE(img_ebike_arrow_left);
    lv_obj_t * icon1 = lv_image_create(top_cont);
    lv_image_set_src(icon1, &img_ebike_arrow_left);

    LV_IMAGE_DECLARE(img_ebike_lamp);
    lv_obj_t * icon2 = lv_image_create(top_cont);
    lv_image_set_src(icon2, &img_ebike_lamp);

    LV_IMAGE_DECLARE(img_ebike_arrow_right);
    lv_obj_t * icon3 = lv_image_create(top_cont);
    lv_image_set_src(icon3, &img_ebike_arrow_right);

    lv_obj_t * roller_cont = lv_obj_create(dashboard_center_cont);
    lv_obj_set_size(roller_cont, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_style_bg_opa(roller_cont, 0, 0);
    lv_obj_align(roller_cont, LV_ALIGN_CENTER, 0, 0);

    const char * opts1 = "0\n1\n2\n3\n4\n5\n6\n7\n8\n9";
    lv_obj_t * roller1 = roller_create(roller_cont, opts1, LV_ROLLER_MODE_NORMAL);
    lv_obj_align(roller1, LV_ALIGN_LEFT_MID, 0, 0);

    const char * opts2 = "0\n1\n2\n3\n4\n5\n6\n7\n8\n9";
    lv_obj_t * roller2 = roller_create(roller_cont, opts2, LV_ROLLER_MODE_INFINITE);
    lv_obj_align(roller2, LV_ALIGN_LEFT_MID, 50, 0);

    return left_cont;
}

static lv_obj_t * roller_create(lv_obj_t * parent, const char * opts, lv_roller_mode_t mode)
{
    LV_FONT_DECLARE(font_ebike_130);
    lv_obj_t * roller = lv_roller_create(parent);
    lv_obj_set_style_text_font(roller, &font_ebike_130, 0);
    lv_obj_set_style_text_align(roller, LV_TEXT_ALIGN_CENTER, 0);
    lv_roller_set_options(roller, opts, mode);
    lv_roller_set_visible_row_count(roller, 1);
    lv_obj_set_width(roller, 50);
    lv_obj_set_style_anim_duration(roller, 300, 0);
    lv_obj_set_style_bg_opa(roller, 0, LV_PART_MAIN);
    lv_obj_set_style_bg_opa(roller, 0, LV_PART_SELECTED);

    return roller;
}


static lv_obj_t * card_labels_create(lv_obj_t * parent, const char * value, const char * unit, const char * title)
{
    lv_obj_t * main_cont = lv_obj_create(parent);
    lv_obj_set_size(main_cont, lv_pct(100), lv_pct(100));
    lv_obj_set_style_bg_opa(main_cont, 0, 0);

    lv_obj_t * center_cont = lv_obj_create(main_cont);
    lv_obj_set_flex_flow(center_cont, LV_FLEX_FLOW_ROW);
    lv_obj_set_style_flex_main_place(center_cont, LV_FLEX_ALIGN_CENTER, 0);
    lv_obj_set_style_flex_cross_place(center_cont, LV_FLEX_ALIGN_START, 0);
    lv_obj_set_size(center_cont, lv_pct(100), LV_SIZE_CONTENT);
    lv_obj_set_style_bg_opa(center_cont, 0, 0);

    LV_FONT_DECLARE(font_ebike_56);
    lv_obj_center(center_cont);
    lv_obj_t * label;
    label = lv_label_create(center_cont);
    lv_label_set_text(label, value);
    lv_obj_set_style_text_font(label, &font_ebike_56, 0);

    LV_FONT_DECLARE(font_ebike_19);
    label = lv_label_create(center_cont);
    lv_label_set_text(label, unit);
    lv_obj_set_style_text_font(label, &font_ebike_19, 0);

    label = lv_label_create(main_cont);
    lv_label_set_text(label, title);
    lv_obj_set_style_text_font(label, &font_ebike_19, 0);
    lv_obj_align(label, LV_ALIGN_BOTTOM_MID, 0, -8);

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

    lv_obj_t * battery = lv_bar_create(right_cont);
    lv_obj_set_size(battery, lv_pct(100), lv_pct(100));
    lv_obj_set_flex_grow(battery, 1);
    lv_obj_set_flex_flow(battery, LV_FLEX_FLOW_ROW);
    lv_obj_set_scroll_snap_x(battery, LV_SCROLL_SNAP_CENTER);
    lv_obj_add_flag(battery, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_border_color(battery, EBIKE_COLOR_LIME, 0);
    lv_obj_set_style_border_width(battery, 4, 0);
    lv_obj_set_style_bg_opa(battery, 0, 0);
    lv_obj_set_style_pad_all(battery, 10, 0);
    lv_obj_set_style_bg_opa(battery, 0, 0);
    lv_obj_set_style_radius(battery, 12, 0);
    lv_obj_set_style_bg_color(battery, EBIKE_COLOR_LIME, LV_PART_INDICATOR);
    //  lv_obj_set_style_text_color(battery, lv_color_black(), 0);
    lv_obj_set_style_radius(battery, 6, LV_PART_INDICATOR);
    lv_bar_set_value(battery, 30, LV_ANIM_ON);

    card_labels_create(battery, "16.4", "km", "Distance today");
    card_labels_create(battery, "36.4", "asd", "Asdasda ds");

    lv_obj_t * dist = lv_obj_create(right_cont);
    lv_obj_set_size(dist, lv_pct(100), lv_pct(100));
    lv_obj_set_style_pad_all(dist, 14, 0);
    lv_obj_set_flex_grow(dist, 1);
    lv_obj_set_style_radius(dist, 12, 0);
    lv_obj_set_style_bg_color(dist, EBIKE_COLOR_TURQUOISE, 0);
    lv_obj_set_style_text_color(dist, lv_color_black(), 0);
    lv_obj_set_flex_flow(dist, LV_FLEX_FLOW_ROW);
    lv_obj_set_scroll_snap_x(dist, LV_SCROLL_SNAP_CENTER);


    card_labels_create(dist, "16.4", "km", "Distance today");
    card_labels_create(dist, "36.4", "asd", "Asdasda ds");
    card_labels_create(dist, "76.4", "GGGG", "ddff asdas ");

    return right_cont;
}

