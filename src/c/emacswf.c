#include <pebble.h>
static Window *s_main_window;
static TextLayer *s_time_layer;
static TextLayer *s_scratch_layer;
static TextLayer *s_menu_layer;
static TextLayer *s_minor_layer;

static void main_window_load(Window *window) {

  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  // GRect(x,y,w,h)
  s_menu_layer = text_layer_create(
				   GRect(0, 0, 144, 20));
  s_scratch_layer = text_layer_create(
				      GRect(0, 19, 144, 129));
  s_minor_layer = text_layer_create(
				    GRect(0, 148, 144, 21));
  s_time_layer = text_layer_create(
				   GRect(110, 148, 30, 21));
  
  // Menu Bar
  text_layer_set_background_color(s_menu_layer, GColorWhite);
  text_layer_set_text_color(s_menu_layer, GColorBlack);
  text_layer_set_font(s_menu_layer, fonts_get_system_font(FONT_KEY_GOTHIC_14));
  text_layer_set_text_alignment(s_menu_layer, GTextAlignmentLeft);
  text_layer_set_text(s_menu_layer, "File Edit Options Buffers Tools Lisp-Interaction Help");
  // Scratch Buffer
  text_layer_set_background_color(s_scratch_layer, GColorBlack);
  text_layer_set_text_color(s_scratch_layer, GColorLightGray);
  text_layer_set_font(s_scratch_layer, fonts_get_system_font(FONT_KEY_GOTHIC_14));
  text_layer_set_text_alignment(s_scratch_layer, GTextAlignmentLeft);
  text_layer_set_text(s_scratch_layer, ";; This buffer is for text that \nis not saved, and for Lisp \nevaluation. \n;; To create a file, visit it \nwith C-x C-f and enter text \nin its buffer.");
  // Mode Line
  text_layer_set_background_color(s_minor_layer, GColorLightGray);
  text_layer_set_text_color(s_minor_layer, GColorWhite);
  text_layer_set_font(s_minor_layer, fonts_get_system_font(FONT_KEY_GOTHIC_14));
  text_layer_set_text_alignment(s_minor_layer, GTextAlignmentLeft);
  text_layer_set_text(s_minor_layer, "U:-- *scratch* (Lisp)");
  // Time Layer
  text_layer_set_background_color(s_time_layer, GColorLightGray);
  text_layer_set_text_color(s_time_layer, GColorWhite);
  text_layer_set_font(s_time_layer, fonts_get_system_font(FONT_KEY_GOTHIC_14));
  text_layer_set_text_alignment(s_time_layer, GTextAlignmentRight);
  
  layer_add_child(window_layer, text_layer_get_layer(s_menu_layer));
  layer_add_child(window_layer, text_layer_get_layer(s_scratch_layer));
  layer_add_child(window_layer, text_layer_get_layer(s_minor_layer));
  layer_add_child(window_layer, text_layer_get_layer(s_time_layer));
}

static void main_window_unload(Window *window) {
  window_destroy(s_main_window);
  text_layer_destroy(s_time_layer);
  text_layer_destroy(s_minor_layer);
  text_layer_destroy(s_menu_layer);
  text_layer_destroy(s_scratch_layer);

}

static void update_time() {
  time_t temp = time(NULL);
  struct tm *tick_time = localtime(&temp);

  static char s_buffer[8];
    strftime(s_buffer, sizeof(s_buffer), clock_is_24h_style() ?
	     "%H:%M" : "%I:%M", tick_time);

  text_layer_set_text(s_time_layer, s_buffer);

}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_time();
}

static void init() {
  s_main_window = window_create();

  window_set_window_handlers(s_main_window, (WindowHandlers) {
      .load = main_window_load,
	.unload = main_window_unload
	});
	
  window_stack_push(s_main_window, true);
  
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);

  update_time();
}

static void deinit() {
 window_destroy(s_main_window);

}

int main() {
  init();
  app_event_loop();
  
}
