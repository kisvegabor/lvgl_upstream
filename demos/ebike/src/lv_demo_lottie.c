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

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
typedef struct {
    Tvg_Paint * tvg_paint;
    Tvg_Canvas * tvg_canvas;
    Tvg_Animation * tvg_anim;
    lv_timer_t * timer;
} lottie_dsc_t;

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void delete_event_cb(lv_event_t * e);
static void anim_timer_cb(lv_timer_t * t);

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *  GLOBAL VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

lv_obj_t * lv_lottie_create(lv_obj_t * parent, const char * src, size_t src_size, int32_t w, int32_t h, uint8_t * buf)
{

    lottie_dsc_t * dsc = lv_malloc(sizeof(lottie_dsc_t));


    dsc->tvg_anim = tvg_animation_new();

    dsc->tvg_paint = tvg_animation_get_picture(dsc->tvg_anim);
    tvg_picture_load_data(dsc->tvg_paint, src, src_size, "lottie", true);
    tvg_picture_set_size(dsc->tvg_paint, w, h);


    dsc->tvg_canvas = tvg_swcanvas_create();
    tvg_swcanvas_set_target(dsc->tvg_canvas, buf, w, w, h, TVG_COLORSPACE_ARGB8888);
    tvg_canvas_push(dsc->tvg_canvas, dsc->tvg_paint);

    lv_obj_t * lv_canvas =  lv_canvas_create(parent);
    lv_canvas_set_buffer(lv_canvas, buf, w, h, LV_COLOR_FORMAT_ARGB8888);
    lv_obj_set_user_data(lv_canvas, dsc);
    lv_obj_add_event_cb(lv_canvas, delete_event_cb, LV_EVENT_DELETE, NULL);


    dsc->timer = lv_timer_create(anim_timer_cb, 20, lv_canvas);

    return lv_canvas;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/


static void delete_event_cb(lv_event_t * e)
{
    lv_obj_t * canvas = lv_event_get_target(e);
    lottie_dsc_t * dsc = lv_obj_get_user_data(canvas);

    tvg_animation_del(dsc->tvg_anim);
    tvg_canvas_destroy(dsc->tvg_canvas);
    lv_timer_delete(dsc->timer);
    lv_free(dsc);
}

static void anim_timer_cb(lv_timer_t * t)
{
    lv_obj_t * canvas = t->user_data;
    lottie_dsc_t * dsc = lv_obj_get_user_data(canvas);

    float f_total;
    float f;
    tvg_animation_get_total_frame(dsc->tvg_anim, &f_total);
    tvg_animation_get_frame(dsc->tvg_anim, &f);

    f++;
    if(f >= f_total) f = 0;

    tvg_animation_set_frame(dsc->tvg_anim, f);
    tvg_canvas_update(dsc->tvg_canvas);
    tvg_canvas_draw(dsc->tvg_canvas);
    tvg_canvas_sync(dsc->tvg_canvas);
    lv_obj_invalidate(canvas);
}
