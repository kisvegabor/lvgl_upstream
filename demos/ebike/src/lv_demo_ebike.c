/**
 * @file lv_demo_ebike.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lv_demo_ebike.h"
#include "lv_demo_ebike_home.h"
#include "lv_demo_ebike_settings.h"
#include "lv_demo_ebike_stat.h"
#include "translations/lv_i18n.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void screen_orientation_observer_cb(lv_observer_t * observer, lv_subject_t * subject);
static void language_observer_cb(lv_observer_t * observer, lv_subject_t * subject);
static void menu_item_click_event_cb(lv_event_t * e);
static void anim_timer_cb(lv_timer_t * t);

/**********************
 *  STATIC VARIABLES
 **********************/
static lv_obj_t * main_cont;
static lv_obj_t * menu_cont;

/**********************
 *  GLOBAL VARIABLES
 **********************/
lv_subject_t ebike_subject_speed_arc;
lv_subject_t ebike_subject_speed_roller;
lv_subject_t ebike_subject_portrait;
lv_subject_t ebike_subject_language;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lv_demo_ebike_create(void)
{
    lv_i18n_init(lv_i18n_language_pack);

    if(lv_group_get_default() == NULL) {
        lv_group_set_default(lv_group_create());
    }

    lv_subject_init_int(&ebike_subject_speed_arc, 0);
    lv_subject_init_int(&ebike_subject_speed_roller, 0);
    lv_subject_init_int(&ebike_subject_portrait, true);
    lv_subject_init_int(&ebike_subject_language, 0);
    lv_demo_ebike_stat_init();

    lv_display_t * display = lv_display_get_default();
    lv_theme_t * theme = lv_theme_simple_init(display);
    lv_display_set_theme(display, theme);

    lv_obj_set_flex_flow(lv_screen_active(), LV_FLEX_FLOW_ROW);
    lv_obj_remove_flag(lv_screen_active(), LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_text_color(lv_screen_active(), lv_color_white(), 0);

    lv_obj_t * bg = lv_image_create(lv_screen_active());

    //    LV_IMAGE_DECLARE(img_ebike_bg);
    //    lv_image_set_src(bg, &img_ebike_bg);

    LV_IMAGE_DECLARE(img_ebike_bg_large);
    lv_image_set_src(bg, &img_ebike_bg_large);

    lv_obj_align(bg, LV_ALIGN_CENTER, 0, 0);
    lv_obj_add_flag(bg, LV_OBJ_FLAG_IGNORE_LAYOUT);
    lv_image_set_inner_align(bg, LV_IMAGE_ALIGN_TILE);
    lv_obj_set_style_bg_color(lv_screen_active(), lv_color_hex(0x004488), 0);

    main_cont = lv_obj_create(lv_screen_active());
    lv_obj_set_size(main_cont, lv_pct(100), lv_pct(100));
    lv_obj_set_flex_grow(main_cont, 1);
    lv_obj_set_style_bg_opa(main_cont, 0, 0);

    lv_demo_ebike_home_create(main_cont);
    //    lv_demo_ebike_stat_create(main_cont);

    menu_cont = lv_obj_create(lv_screen_active());
    lv_obj_set_style_bg_color(menu_cont, lv_color_black(), 0);
    lv_obj_set_size(menu_cont, 44 * 2.5, lv_pct(100));
    lv_obj_set_flex_flow(menu_cont, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(menu_cont, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_style_pad_gap(menu_cont, 16 * 2.5, 0);

    LV_IMAGE_DECLARE(img_ebike_settings);
    lv_obj_t * icon1 = lv_image_create(menu_cont);
    lv_image_set_src(icon1, &img_ebike_settings);
    lv_obj_add_event_cb(icon1, menu_item_click_event_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_set_size(icon1, 44 * 2.5, 44 * 2.5);
    lv_obj_set_ext_click_area(icon1, 8 * 2.5);
    lv_obj_add_flag(icon1, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_image_opa(icon1, LV_OPA_50, 0);

    LV_IMAGE_DECLARE(img_ebike_stat);
    lv_obj_t * icon2 = lv_image_create(menu_cont);
    lv_image_set_src(icon2, &img_ebike_stat);
    lv_obj_add_event_cb(icon2, menu_item_click_event_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_set_size(icon2, 44 * 2.5, 44 * 2.5);
    lv_obj_set_ext_click_area(icon2, 8 * 2.5);
    lv_obj_add_flag(icon2, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_image_opa(icon2, LV_OPA_50, 0);

    LV_IMAGE_DECLARE(img_ebike_home);
    lv_obj_t * icon3 = lv_image_create(menu_cont);
    lv_image_set_src(icon3, &img_ebike_home);
    lv_obj_add_event_cb(icon3, menu_item_click_event_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_set_size(icon3, 44 * 2.5, 44 * 2.5);
    lv_obj_set_ext_click_area(icon3, 8 * 2.5);
    lv_obj_add_flag(icon3, LV_OBJ_FLAG_CLICKABLE);

    lv_subject_add_observer_obj(&ebike_subject_portrait, screen_orientation_observer_cb, lv_screen_active(), NULL);
    lv_subject_add_observer_obj(&ebike_subject_language, language_observer_cb, lv_screen_active(), NULL);

    lv_timer_create(anim_timer_cb, 2000, NULL);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/


static void set_subject_exec_cb(void * var, int32_t v)
{
    lv_subject_set_int(var, v);
}

static void anim_timer_cb(lv_timer_t * t)
{
    int32_t v = lv_rand(0, 90);

    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, &ebike_subject_speed_arc);
    lv_anim_set_values(&a, lv_subject_get_int(&ebike_subject_speed_arc), v);
    lv_anim_set_duration(&a, 1800);
    lv_anim_set_exec_cb(&a, set_subject_exec_cb);
    lv_anim_start(&a);
    lv_anim_start(&a);

}

static void menu_item_click_event_cb(lv_event_t * e)
{

    lv_obj_clean(main_cont);

    lv_obj_t  * icon = lv_event_get_target(e);
    uint32_t idx = lv_obj_get_index(icon);

    lv_obj_set_style_image_opa(lv_obj_get_child(menu_cont, 0), LV_OPA_50, 0);
    lv_obj_set_style_image_opa(lv_obj_get_child(menu_cont, 1), LV_OPA_50, 0);
    lv_obj_set_style_image_opa(lv_obj_get_child(menu_cont, 2), LV_OPA_50, 0);

    lv_obj_set_style_image_opa(lv_obj_get_child(menu_cont, idx), LV_OPA_100, 0);
    switch(idx) {
        case 0:
            lv_demo_ebike_settings_create(main_cont);
            break;
        case 1:
            lv_demo_ebike_stat_create(main_cont);
            break;
        case 2:
            lv_demo_ebike_home_create(main_cont);
            break;
        default:
            break;
    }
}

static void language_observer_cb(lv_observer_t * observer, lv_subject_t * subject)
{
    static uint32_t lang_current = 0;
    uint32_t lang_new = lv_subject_get_int(subject);
    if(lang_new != lang_current) {
        lang_current = lang_new;
        switch(lang_current) {
            case 0:
                lv_i18n_set_locale("en");
                break;
            case 1:
                lv_i18n_set_locale("zh");
                break;
            case 2:
                lv_i18n_set_locale("ar");
                break;
        }
        lv_obj_clean(main_cont);
        lv_demo_ebike_settings_create(main_cont);
    }
}

static void screen_orientation_observer_cb(lv_observer_t * observer, lv_subject_t * subject)
{
    bool portrait = lv_subject_get_int(&ebike_subject_portrait);

    if(portrait) {
        lv_obj_set_size(menu_cont, lv_pct(100), 44 * 2.5);
        lv_obj_set_flex_flow(menu_cont, LV_FLEX_FLOW_ROW);
        lv_obj_set_flex_flow(lv_screen_active(), LV_FLEX_FLOW_COLUMN);
        lv_obj_update_layout(lv_screen_active());
        lv_obj_set_flex_flow(lv_screen_active(), LV_FLEX_FLOW_COLUMN);
    }
    else {
        lv_obj_set_size(menu_cont, 44 * 2.5, lv_pct(100));
        lv_obj_set_flex_flow(menu_cont, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_flex_flow(lv_screen_active(), LV_FLEX_FLOW_ROW);
        lv_obj_update_layout(lv_screen_active());
        lv_obj_set_flex_flow(lv_screen_active(), LV_FLEX_FLOW_ROW);
    }
}
