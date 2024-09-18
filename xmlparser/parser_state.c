#include "parser_state.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct
{
	const char * name;
	lv_obj_t * (*process_cb)(ParserState *, lv_obj_t * ,const char ** attrs);
}widget_process_t;


lv_align_t align_string_to_value(const char * txt)
{
	if(streq(txt, "center")) return LV_ALIGN_CENTER;
	if(streq(txt, "top_left")) return LV_ALIGN_TOP_LEFT;
	if(streq(txt, "bottom_right")) return LV_ALIGN_BOTTOM_RIGHT;

	LV_LOG_WARN("%s is an unknown align value", txt);
	return 0;
}

static lv_style_t * get_style(ParserState * state, const char * name)
{
	xml_style_t * xml_style;
	LV_LL_READ(&state->style_ll, xml_style) {
		if(streq(xml_style->name, name)) return &xml_style->style;
	}

	LV_LOG_WARN("No style found with %s name", name);

	return NULL;
}

static void style_str_process(ParserState * state, lv_obj_t * obj, const char * text)
{
    // Duplicate the input text to avoid modifying the original string
    char str[512];
    strncpy(str, text, sizeof(str) - 1);
    str[sizeof(str) - 1] = '\0';  // Ensure null termination

    uint32_t selector = 0; // This will hold the selector for state and part
    char *style_name = NULL;

    // Split the string based on space and colons
    char * onestyle_state = NULL;
    char *onestyle_str = strtok_r(str, " ", &onestyle_state);
    while (onestyle_str != NULL) {
		// Parse the parts and states after the space
		char * selector_state = NULL;
        style_name = strtok_r(onestyle_str, ":", &selector_state);
		char * selector_str = strtok_r(NULL, ":", &selector_state);
		while (selector_str != NULL) {
			// Handle different states and parts
			if (streq(selector_str, "pressed")) selector |= LV_STATE_PRESSED;
			else if (streq(selector_str, "checked")) selector |= LV_STATE_CHECKED;
			else if (streq(selector_str, "indicator")) selector |= LV_PART_INDICATOR;
			else if (streq(selector_str, "scrollbar")) selector |= LV_PART_SCROLLBAR;
			else if (streq(selector_str, "main")) selector |= LV_PART_MAIN;

			// Move to the next token
			selector_str = strtok_r(NULL, ":", &selector_state);
		}

		// Apply the selector-based style if valid
		if (style_name != NULL) {
			lv_style_t *style = get_style(state, style_name);
			if (style) {
				lv_obj_add_style(obj, style, selector); // Apply with the built selector
			}
		}
		onestyle_str = strtok_r(NULL, " ", &onestyle_state);
    }
}


void obj_apply_attrs(ParserState * state, lv_obj_t * obj, const char ** attrs)
{
	for(int i = 0; attrs[i]; i += 2) {
		const char * name = attrs[i];
		const char * value = attrs[i + 1];
		if (streq(name, "styles")) style_str_process(state, obj, value);
		else if (streq(name, "width")) lv_obj_set_width(obj, atoi(value));
		else if (streq(name, "height")) lv_obj_set_height(obj, atoi(value));
		else if (streq(name, "x")) lv_obj_set_x(obj, atoi(value));
		else if (streq(name, "y")) lv_obj_set_y(obj, atoi(value));
		else if (streq(name, "align")) lv_obj_set_align(obj, align_string_to_value(value));
	}

}

static lv_obj_t * obj_process_cb(ParserState * state, lv_obj_t * parent, const char **attrs)
{
	lv_obj_t * obj = lv_obj_create(parent);
	obj_apply_attrs(state, obj, attrs);

	return obj;
}

static lv_obj_t * button_process_cb(ParserState * state, lv_obj_t * parent, const char **attrs)
{
	lv_obj_t * obj = lv_button_create(parent);
	obj_apply_attrs(state, obj, attrs);

	return obj;
}

static lv_slider_mode_t slider_mode_string_to_value(const char * txt)
{
	if(streq(txt, "normal")) return LV_SLIDER_MODE_NORMAL;
	if(streq(txt, "symmetrical")) return LV_SLIDER_MODE_SYMMETRICAL;
	if(streq(txt, "range")) return LV_SLIDER_MODE_RANGE;

	LV_LOG_WARN("%s is an unknown slider mode value", txt);
	return 0;
}


static lv_obj_t * slider_process_cb(ParserState * state, lv_obj_t * parent, const char **attrs)
{
	lv_obj_t * obj = lv_slider_create(parent);
	obj_apply_attrs(state, obj, attrs);

	for(int i = 0; attrs[i]; i += 2) {
		const char * name = attrs[i];
		const char * value = attrs[i + 1];
		if (strcmp(name, "value") == 0) lv_slider_set_value(obj, atoi(value), LV_ANIM_OFF);
		else if (strcmp(name, "mode") == 0) lv_slider_set_mode(obj, slider_mode_string_to_value(value));

	}

	return obj;
}

static lv_label_long_mode_t label_long_mode_string_to_value(const char * txt)
{
	if(streq(txt, "wrap")) return LV_LABEL_LONG_WRAP;
	if(streq(txt, "dot")) return LV_LABEL_LONG_DOT;
	if(streq(txt, "long_scroll")) return LV_LABEL_LONG_SCROLL;
	if(streq(txt, "scroll_circular")) return LV_LABEL_LONG_SCROLL_CIRCULAR;
	if(streq(txt, "clip")) return LV_LABEL_LONG_CLIP;

	LV_LOG_WARN("%s is an unknown label long mode value", txt);
	return 0;
}

static lv_obj_t * label_process_cb(ParserState * state, lv_obj_t * parent, const char **attrs)
{
	lv_obj_t * obj = lv_label_create(parent);
	obj_apply_attrs(state, obj, attrs);

	for(int i = 0; attrs[i]; i += 2) {
		const char * name = attrs[i];
		const char * value = attrs[i + 1];
		 if (streq(name, "text"))lv_label_set_text(obj, value);
		 else if (streq(name, "long_mode")) lv_label_set_long_mode(obj, label_long_mode_string_to_value(value));
	}

	return obj;
}


widget_process_t widget_processors[] =
{
		{.name = "obj", .process_cb = obj_process_cb},
		{.name = "button", .process_cb = button_process_cb},
		{.name = "slider", .process_cb = slider_process_cb},
		{.name = "label", .process_cb = label_process_cb},
		{.name = NULL, .process_cb = NULL}
};

const char * lv_xml_get_value_of(const char **attrs, const char * name)
{
	for(int i = 0; attrs[i]; i += 2) {
		if(streq(attrs[i], name)) return attrs[i + 1];
	}

	LV_LOG_WARN("No value found for name:%s", name);
	return NULL;
}

void style_process(ParserState *state, const char **attrs)
{
	const char * style_name =  lv_xml_get_value_of(attrs, "name");
	xml_style_t * xml_style = lv_ll_ins_tail(&state->style_ll);
	lv_style_t * style = &xml_style->style;
	lv_style_init(style);
	xml_style->name = lv_strdup(style_name);

	for(int i = 0; attrs[i]; i += 2) {
		const char * name = attrs[i];
		const char * value = attrs[i + 1];
		if(streq(name, "name")) continue;
		if(streq(name, "help")) continue;
		if(streq(name, "bg_color")) lv_style_set_bg_color(style, lv_color_hex(strtol(value, NULL, 16)));
		else {
			LV_LOG_WARN("%s style property is not supported", name);
		}
	}
}

// Start element handler
void start_element_handler(void *userData, const char *name, const char **attrs) {

    ParserState *state = (ParserState *)userData;
    bool is_view = false;
	if(streq(name, "view")) {
		const char * extends = lv_xml_get_value_of(attrs, "extends");
		name = extends ? extends : "obj";
		is_view = true;
	}

    /*Select the widget specific parser type based on the name*/
    if(streq(name, "styles")) return;
    else if(streq(name, "style")) style_process(state, attrs);
    else {
		lv_obj_t ** current_parent_p = lv_ll_get_tail(&state->parent_ll);
		lv_obj_t * current_parent;
		if(current_parent_p == NULL) current_parent = lv_screen_active();
		else current_parent = *current_parent_p;
		void * item = NULL;
		if(streq(name, "obj")) item = obj_process_cb(state, current_parent, attrs);
		if(streq(name, "button")) item = button_process_cb(state, current_parent, attrs);
		if(streq(name, "slider")) item = slider_process_cb(state, current_parent, attrs);
		if(streq(name, "label")) item = label_process_cb(state, current_parent, attrs);

		if(item == NULL) {
			LV_LOG_WARN("%s in not a known widget", name);
			return;
		}

		lv_obj_t ** new_parent = lv_ll_ins_tail(&state->parent_ll);
		*new_parent = item;

		if(is_view) {
			state->view = item;
		}
    }
}


// End element handler
void end_element_handler(void *userData, const char *name) {
    ParserState *state = (ParserState *)userData;

    lv_obj_t ** current_parent = lv_ll_get_tail(&state->parent_ll);
    if(current_parent) lv_ll_remove(&state->parent_ll, current_parent);
}


char *strip(char *str) {
    char *end;

    // Trim leading spaces
    while (isspace((unsigned char)*str)) str++;

    if (*str == 0) { // All spaces?
        return str;
    }

    // Trim trailing spaces
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;

    // Write new null terminator
    *(end + 1) = '\0';

    return str;
}

// Character data handler
void character_data_handler(void *userData, const char *s, int len) {

	char t[1000] = {};
	memcpy(t, s, len);
	t[len] = '\0';
	const char * t2 = strip(t);
	if(strlen(t2)) printf("%s\n", t2);

    // Handle character data if needed
}
