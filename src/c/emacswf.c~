#include <pebble.h>
static Window *s_main_window;
static TextLayer *s_time_layer;

static void main_window_load(Window *window) {

  // Get Information about Window
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  // Create text layer at bounds specified
  s_time_layer = text_layer_create(
				   GRect(0, PBL_IF_ROUND_ELSE(58,52), bounds.size.w, 50));

  // Improve Layout to create watchface
  text_layer_set_background_colors(s_time_layer, GColorBlack);
  text_layer_set_text_color(s_time_layer, GColorWhite);
  text_layer_set_text(s_time_layer, "00:00");
  text_layer_set_font(s_time_layer, fonts_get_system_font(FONT_KEY_BITHAM_42_B));
  text_layer_set_text_alignment(s_time_layer, GTextAlignmentCenter);

  // Add s_time_layer as child of s_window_layer
  layer_add_child(window_layer, text_layer,get_layers(s_time_layer));

}

static void main_window_unload(Window *window) {
  // Destroy Main Static Window
  window_destroy(s_main_window);
  text_layer_destroy(s_time_layer);

}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_time();

}

static void update_time() {
  // Get tm struct
  time_t temp = time(NULL);
  struct tm *tick_time = localtime(&temp);

  // Write hours and minutes from tm struct to buffer
  static char s_buffer[8]
    strftime(s_buffer, sizeof(s_buffer), clock_is_24h_style() ?
	     "%H:%M" : "%I:%M", tick_time);

  // Display time on s_text_layer
  text_layout_set_text(s_time_layer, s_buffer);

}

static void init() {
  // Create main window element and assign to pointer
  s_main_window = window_create();

  // Set handlers to manage the elements inside the window
  window_set_window_handlers(s_main_window, (WindowHandlers) {
      .load = main_window_load,
	.unload = main_window_unload
	});

  // Show the window on the watch, animation enabled
  window_stack_push(s_main_window, true);
  
  // TickTimerService
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
  
  // Load tm struct from start
  update_time();
  
}

static void deinit() {

int main(void) {
  init();
  app_event_loop();
  deinit();
}

}

