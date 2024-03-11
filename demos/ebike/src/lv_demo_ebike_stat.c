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
typedef enum {
    MODE_AVG_SPEED,
    MODE_DISTANCE,
    MODE_TOP_SPEED,
} stat_mode_t;

/**********************
 *  STATIC PROTOTYPES
 **********************/
static lv_obj_t * left_cont_create(lv_obj_t * parent);
static lv_obj_t * right_cont_create(lv_obj_t * parent);
static lv_subject_t subject_week;
static lv_subject_t subject_day;
static lv_subject_t subject_avg_speed;
static lv_subject_t subject_distance;
static lv_subject_t subject_top_speed;
static lv_subject_t subject_mode;

/**********************
 *  STATIC VARIABLES
 **********************/
static int32_t top_speed_values[] = {46, 28, 42, 39, 41, 25, 49, 37, 35, 40, 33, 40, 31, 27, 45, 38, 41, 40, 27, 25, 30, 45, 31, 43, 41, 34, 47, 32, 30, 33};
static int32_t avg_speed_values[] = {21, 24, 27, 29, 23, 28, 28, 22, 29, 28, 24, 26, 24, 30, 25, 25, 20, 28, 24, 27, 25, 27, 20, 29, 25, 24, 23, 26, 27, 27};
static int32_t distance_values[] =  {87, 63, 29, 84, 27, 84, 33, 76, 77, 49, 46, 29, 67, 21, 87, 75, 40, 19, 12, 67, 66, 11, 59, 33, 51, 75, 44, 61, 53, 63};

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lv_demo_ebike_stat_init(void)
{
    lv_subject_init_int(&subject_mode, MODE_DISTANCE);
    lv_subject_init_int(&subject_week, 0);
    lv_subject_init_int(&subject_day, 0);
    lv_subject_init_int(&subject_top_speed, 0);
    lv_subject_init_int(&subject_avg_speed, 0);
    lv_subject_init_int(&subject_distance, 0);
}

void lv_demo_ebike_stat_create(lv_obj_t * parent)
{
    lv_obj_t * main_cont = lv_obj_create(parent);
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
static void tabs_click_event_cb(lv_event_t * e)
{
    lv_obj_t * btnm = lv_event_get_target(e);
    lv_subject_set_int(&subject_mode, lv_buttonmatrix_get_selected_button(btnm));
}

static lv_obj_t * tabs_create(lv_obj_t * parent)
{
    lv_obj_t * btnm = lv_buttonmatrix_create(parent);
    lv_obj_set_size(btnm, lv_pct(100), 21);
    lv_obj_set_style_bg_opa(btnm, 0, 0);
    lv_obj_set_style_bg_opa(btnm, 0, LV_PART_ITEMS);
    lv_obj_set_style_border_width(btnm, 1, LV_PART_ITEMS);
    lv_obj_set_style_border_width(btnm, 2, LV_PART_ITEMS | LV_STATE_FOCUSED);
    lv_obj_set_style_border_side(btnm, LV_BORDER_SIDE_BOTTOM, LV_PART_ITEMS);
    lv_obj_set_style_border_color(btnm, EBIKE_COLOR_TURQUOISE, LV_PART_ITEMS);
    lv_obj_set_style_border_opa(btnm, LV_OPA_20, LV_PART_ITEMS);
    lv_obj_set_style_border_opa(btnm, LV_OPA_COVER, LV_PART_ITEMS | LV_STATE_FOCUSED);
    lv_obj_set_style_text_color(btnm, lv_color_white(), LV_PART_ITEMS);
    lv_obj_set_style_text_color(btnm, EBIKE_COLOR_TURQUOISE, LV_PART_ITEMS | LV_STATE_FOCUSED);
    static const char * texts[] = {"Avg. Speed", "Distance", "Top speed", ""};
    lv_buttonmatrix_set_map(btnm, texts);

    lv_obj_add_event_cb(btnm, tabs_click_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
    lv_buttonmatrix_set_selected_button(btnm, lv_subject_get_int(&subject_mode));

    return btnm;
}

static void left_click_event_cb(lv_event_t * e)
{
    int32_t week = lv_subject_get_int(&subject_week);
    if(week < 1) return;
    lv_subject_set_int(&subject_week, week - 1);
}

static void right_click_event_cb(lv_event_t * e)
{
    int32_t week = lv_subject_get_int(&subject_week);
    if(week >= 3) return;
    lv_subject_set_int(&subject_week, week + 1);
}

static void current_week_observer_cb(lv_observer_t * observer, lv_subject_t * subject)
{
    lv_obj_t * label = lv_observer_get_target_obj(observer);
    int32_t week = lv_subject_get_int(&subject_week);
    lv_label_set_text_fmt(label, "March %d - March %d", week * 7 + 1, week * 7 + 7);
}

static void current_data_objserver_cb(lv_observer_t * observer, lv_subject_t * subject)
{
    lv_obj_t * label = lv_observer_get_target_obj(observer);
    stat_mode_t mode = lv_subject_get_int(&subject_mode);
    int32_t day = lv_subject_get_int(&subject_day);
    switch(mode) {
        case MODE_AVG_SPEED:
            lv_label_set_text_fmt(label, "%dkm/h", avg_speed_values[day]);
            break;
        case MODE_TOP_SPEED:
            lv_label_set_text_fmt(label, "%dkm/h", top_speed_values[day]);
            break;
        case MODE_DISTANCE:
            lv_label_set_text_fmt(label, "%dkm", distance_values[day]);
            break;
    }


}

static lv_obj_t * data_cont_create(lv_obj_t * parent)
{
    lv_obj_t * cont = lv_obj_create(parent);
    lv_obj_set_style_bg_opa(cont, 0, 0);
    lv_obj_set_size(cont, lv_pct(100), LV_SIZE_CONTENT);
    lv_obj_set_style_text_color(cont, lv_color_white(), 0);
    lv_obj_set_flex_flow(cont, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_style_flex_main_place(cont, LV_FLEX_ALIGN_CENTER, 0);
    lv_obj_set_style_flex_cross_place(cont, LV_FLEX_ALIGN_CENTER, 0);
    lv_obj_set_style_flex_track_place(cont, LV_FLEX_ALIGN_SPACE_BETWEEN, 0);

    LV_IMAGE_DECLARE(img_ebike_arrow_left_2);
    LV_IMAGE_DECLARE(img_ebike_arrow_right_2);
    LV_FONT_DECLARE(font_ebike_19);
    LV_FONT_DECLARE(font_ebike_56);

    lv_obj_t * icon = lv_image_create(cont);
    lv_image_set_src(icon, &img_ebike_arrow_left_2);
    lv_obj_set_ext_click_area(icon, 32);
    lv_obj_add_flag(icon, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(icon, left_click_event_cb, LV_EVENT_CLICKED, NULL);

    lv_obj_t * label = lv_label_create(cont);
    lv_label_set_text(label, "138km");
    lv_obj_set_style_text_font(label, &font_ebike_56, 0);
    lv_obj_add_flag(label, LV_OBJ_FLAG_FLEX_IN_NEW_TRACK);
    lv_subject_add_observer_obj(&subject_mode, current_data_objserver_cb, label, NULL);
    lv_subject_add_observer_obj(&subject_day, current_data_objserver_cb, label, NULL);

    label = lv_label_create(cont);
    lv_label_set_text(label, "March 18 - March 25");
    lv_obj_set_style_text_font(label, &font_ebike_19, 0);
    lv_subject_add_observer_obj(&subject_week, current_week_observer_cb, label, NULL);

    icon = lv_image_create(cont);
    lv_image_set_src(icon, &img_ebike_arrow_right_2);
    lv_obj_set_ext_click_area(icon, 32);
    lv_obj_add_flag(icon, LV_OBJ_FLAG_FLEX_IN_NEW_TRACK);
    lv_obj_add_flag(icon, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(icon, right_click_event_cb, LV_EVENT_CLICKED, NULL);


    return cont;
}
static void chart_click_event_cb(lv_event_t * e)
{
    lv_obj_t * chart = lv_event_get_target(e);
    uint32_t idx = lv_chart_get_pressed_point(chart);
    if(idx == 0) return;

    lv_subject_set_int(&subject_day, idx);

}

static void chart_draw_event_cb(lv_event_t * e)
{
    lv_obj_t * chart = lv_event_get_target(e);
    lv_obj_t * cont = lv_obj_get_parent(chart);
    lv_draw_rect_dsc_t rect_dsc;
    lv_draw_rect_dsc_init(&rect_dsc);
    rect_dsc.bg_opa = LV_OPA_30;

    uint32_t day = lv_subject_get_int(&subject_day);

    lv_point_t p;
    lv_chart_get_point_pos_by_id(chart, lv_chart_get_series_next(chart, NULL), day, &p);
    lv_coord_t w = lv_obj_get_width(cont) / 7;
    lv_area_t a;
    a.x1 = chart->coords.x1 + p.x - w / 2;
    a.x2 = chart->coords.x1 + p.x + w / 2;
    a.y1 = chart->coords.y1;
    a.y2 = chart->coords.y2;
    lv_draw_rect(lv_event_get_layer(e), &rect_dsc, &a);


    char buf[32];
    lv_snprintf(buf, sizeof(buf), "March %d", lv_subject_get_int(&subject_day));
    LV_FONT_DECLARE(font_ebike_19);
    lv_draw_label_dsc_t label_dsc;
    lv_draw_label_dsc_init(&label_dsc);
    label_dsc.font = &font_ebike_19;
    label_dsc.color = lv_color_white();
    label_dsc.text = buf;
    label_dsc.text_local = 1;
    label_dsc.align = LV_TEXT_ALIGN_CENTER;

    a.x1 = chart->coords.x1 + p.x - 100;
    a.x2 = chart->coords.x1 + p.x + 100;
    a.y1 = chart->coords.y2;
    a.y2 = chart->coords.y2 + 20;
    lv_draw_label(lv_event_get_layer(e), &label_dsc, &a);
}


static void chart_refr_ext_draw(lv_event_t * e)
{
    lv_event_set_ext_draw_size(e, 32);
}


static void chart_week_observer_cb(lv_observer_t * observer, lv_subject_t * subject)
{
    int32_t week = lv_subject_get_int(&subject_week);
    lv_subject_set_int(&subject_day, week * 7 + 1);

    lv_obj_t * chart = lv_observer_get_target_obj(observer);
    lv_obj_t * cont = lv_obj_get_parent(chart);

    lv_point_t p;
    lv_chart_get_point_pos_by_id(chart, lv_chart_get_series_next(chart, NULL), week * 7, &p);
    lv_obj_scroll_to_x(cont,  p.x, LV_ANIM_ON);
}

static void chart_mode_observer_cb(lv_observer_t * observer, lv_subject_t * subject)
{
    lv_obj_t * chart = lv_observer_get_target_obj(observer);
    lv_chart_series_t * ser = lv_chart_get_series_next(chart, NULL);

    switch(lv_subject_get_int(&subject_mode)) {
        case MODE_AVG_SPEED:
            lv_chart_set_range(chart, LV_CHART_AXIS_PRIMARY_Y, 0, 30);
            lv_chart_set_ext_y_array(chart, ser, avg_speed_values);
            break;
        case MODE_TOP_SPEED:
            lv_chart_set_range(chart, LV_CHART_AXIS_PRIMARY_Y, 0, 50);
            lv_chart_set_ext_y_array(chart, ser, top_speed_values);
            break;
        case MODE_DISTANCE:
            lv_chart_set_range(chart, LV_CHART_AXIS_PRIMARY_Y, 0, 90);
            lv_chart_set_ext_y_array(chart, ser, distance_values);
            break;
        default:
            break;
    }
}

static void chart_day_observer_cb(lv_observer_t * observer, lv_subject_t * subject)
{
    lv_obj_t * chart = lv_observer_get_target_obj(observer);

    int32_t day = lv_subject_get_int(&subject_day);

    lv_subject_set_int(&subject_avg_speed, avg_speed_values[day]);
    lv_subject_set_int(&subject_distance, distance_values[day]);
    lv_subject_set_int(&subject_top_speed, top_speed_values[day]);

    lv_obj_invalidate(chart);
}

static lv_obj_t * chart_create(lv_obj_t * parent)
{
    lv_obj_t * cont = lv_obj_create(parent);
    lv_obj_set_width(cont, lv_pct(100));
    lv_obj_set_flex_grow(cont, 1);
    lv_obj_set_style_bg_opa(cont, 0, 0);

    lv_obj_t * chart = lv_chart_create(cont);
    lv_obj_set_flex_grow(chart, 1);
    lv_obj_set_size(chart, lv_pct(370), lv_pct(100));
    lv_chart_set_update_mode(chart, LV_CHART_UPDATE_MODE_CIRCULAR);
    lv_chart_set_point_count(chart, 30);
    lv_chart_set_div_line_count(chart, 0, 0);
    lv_obj_set_style_line_width(chart, 3, LV_PART_ITEMS);
    lv_obj_set_style_size(chart, 10, 10, LV_PART_INDICATOR);
    lv_obj_set_style_bg_opa(chart, LV_OPA_COVER, LV_PART_INDICATOR);
    lv_obj_set_style_bg_color(chart, lv_color_black(), LV_PART_INDICATOR);
    lv_obj_set_style_radius(chart, LV_RADIUS_CIRCLE, LV_PART_INDICATOR);
    lv_obj_set_style_border_color(chart, lv_color_black(), LV_PART_INDICATOR);
    lv_obj_set_style_border_width(chart, 2, LV_PART_INDICATOR);
    lv_obj_set_style_border_width(chart, 1, 0);
    lv_obj_set_style_border_side(chart, LV_BORDER_SIDE_BOTTOM, 0);
    lv_obj_set_style_bg_opa(chart, 0, 0);
    lv_obj_set_style_margin_bottom(chart, 24, 0);

    lv_obj_add_event_cb(chart, chart_click_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_add_event_cb(chart, chart_draw_event_cb, LV_EVENT_DRAW_MAIN_BEGIN, NULL);
    lv_obj_add_event_cb(chart, chart_refr_ext_draw, LV_EVENT_REFR_EXT_DRAW_SIZE, NULL);

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

    lv_subject_add_observer_obj(&subject_week, chart_week_observer_cb, chart, NULL);
    lv_subject_add_observer_obj(&subject_mode, chart_mode_observer_cb, chart, NULL);
    lv_subject_add_observer_obj(&subject_day, chart_day_observer_cb, chart, NULL);

    return chart;
}

static lv_obj_t * stat_card_create(lv_obj_t * parent, const char * name, lv_subject_t * subject, const char * fmt)
{
    lv_obj_t * cont = lv_obj_create(parent);
    lv_obj_set_flex_flow(cont, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_grow(cont, 1);
    lv_obj_set_height(cont, LV_SIZE_CONTENT);
    lv_obj_set_style_bg_opa(cont, 0, 0);

    LV_FONT_DECLARE(font_ebike_19);
    LV_FONT_DECLARE(font_ebike_56);
    lv_obj_t * label = lv_label_create(cont);
    lv_label_set_text(label, name);
    lv_obj_set_style_text_font(label, &font_ebike_19, 0);

    label = lv_label_create(cont);
    lv_obj_set_style_text_font(label, &font_ebike_56, 0);
    lv_label_bind_text(label, subject, fmt);

    return cont;
}

static lv_obj_t * stat_cont_create(lv_obj_t * parent)
{
    lv_obj_t * cont = lv_obj_create(parent);
    lv_obj_set_style_bg_opa(cont, 0, 0);
    lv_obj_set_size(cont, lv_pct(100), LV_SIZE_CONTENT);
    lv_obj_set_flex_flow(cont, LV_FLEX_FLOW_ROW);

    stat_card_create(cont, "Avg. speed", &subject_avg_speed, "%dkm/h");
    stat_card_create(cont, "Distance", &subject_distance, "%dkm");
    stat_card_create(cont, "Top speed", &subject_top_speed, "%dkm/h");

    return cont;
}

static lv_obj_t * right_cont_create(lv_obj_t * parent)
{
    lv_obj_t * right_cont = lv_obj_create(parent);
    lv_obj_set_style_bg_opa(right_cont, 0, 0);
    lv_obj_set_flex_flow(right_cont, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_style_pad_ver(right_cont, 12, 0);
    lv_obj_set_style_pad_right(right_cont, 8, 0);
    lv_obj_set_style_pad_gap(right_cont, 8, 0);
    lv_obj_set_height(right_cont, lv_pct(100));

    tabs_create(right_cont);
    data_cont_create(right_cont);
    chart_create(right_cont);
    stat_cont_create(right_cont);

    return right_cont;
}
