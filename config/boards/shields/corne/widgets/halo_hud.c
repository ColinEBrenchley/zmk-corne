#include "halo_hud.h"
#include <zmk/display.h>
#include <zmk/wpm.h>
#include <zmk/events/wpm_state_changed.h>
#include <zmk/events/battery_state_changed.h>
#include <zmk/events/ble_active_profile_changed.h>

#define CYAN_COLOR lv_color_make(0, 255, 255)

// Keep track of WPM label
static lv_obj_t *wpm_label;

static void draw_halo_frame(lv_obj_t *obj, lv_draw_ctx_t *draw_ctx) {
    lv_draw_line_dsc_t line_dsc;
    lv_draw_line_dsc_init(&line_dsc);
    line_dsc.width = 1;
    line_dsc.color = CYAN_COLOR;

    // Main hexagonal frame points for ammo counter style
    const lv_point_t hex_points[] = {
        {15, 2},  {49, 2},    // Top line
        {62, 16},             // Top right corner
        {49, 30}, {15, 30},   // Bottom line
        {2, 16},              // Top left corner
        {15, 2}               // Close the shape
    };

    // Draw main hexagonal frame
    for (int i = 0; i < 6; i++) {
        lv_point_t p1 = {hex_points[i].x, hex_points[i].y};
        lv_point_t p2 = {hex_points[i + 1].x, hex_points[i + 1].y};
        lv_draw_line(draw_ctx, &line_dsc, &p1, &p2);
    }

    // Draw inner decorative lines
    const lv_point_t inner_lines[][2] = {
        {{15, 8}, {49, 8}},    // Upper horizontal accent
        {{15, 24}, {49, 24}},  // Lower horizontal accent
        {{20, 2}, {20, 8}},    // Left vertical accent
        {{44, 2}, {44, 8}},    // Right vertical accent
    };

    for (int i = 0; i < 4; i++) {
        lv_draw_line(draw_ctx, &line_dsc, &inner_lines[i][0], &inner_lines[i][1]);
    }
}

static void update_wpm(struct zmk_widget_halo_hud *widget) {
    uint8_t wpm = zmk_wpm_get_state();
    char text[8];
    snprintf(text, sizeof(text), "%d", wpm);
    lv_label_set_text(widget->wpm_label, text);
}

static void update_battery(struct zmk_widget_halo_hud *widget) {
    if (widget->battery_label == NULL) { return; }
    
    char text[8];
    snprintf(text, sizeof(text), "%d%%", zmk_battery_state_get_percentage());
    lv_label_set_text(widget->battery_label, text);
}

static void add_ui_elements(struct zmk_widget_halo_hud *widget) {
    static lv_style_t style_text;
    lv_style_init(&style_text);
    lv_style_set_text_color(&style_text, CYAN_COLOR);
    lv_style_set_text_font(&style_text, &lv_font_montserrat_14);

    // WPM counter (centered like ammo counter)
    widget->wpm_label = lv_label_create(widget->obj);
    lv_obj_add_style(widget->wpm_label, &style_text, 0);
    lv_obj_align(widget->wpm_label, LV_ALIGN_CENTER, 0, 0);
    update_wpm(widget);

    // Battery indicator (right side)
    widget->battery_label = lv_label_create(widget->obj);
    lv_obj_add_style(widget->battery_label, &style_text, 0);
    lv_label_set_text(widget->battery_label, "100%");
    lv_obj_align(widget->battery_label, LV_ALIGN_RIGHT_MID, -5, 0);

    // Connection status (left side)
    widget->bluetooth_label = lv_label_create(widget->obj);
    lv_obj_add_style(widget->bluetooth_label, &style_text, 0);
    lv_label_set_text(widget->bluetooth_label, "BT");
    lv_obj_align(widget->bluetooth_label, LV_ALIGN_LEFT_MID, 5, 0);
}

static void hud_update_cb(void *user_data) {
    struct zmk_widget_halo_hud *widget = user_data;
    update_wpm(widget);
    update_battery(widget);
}

int zmk_widget_halo_hud_init(struct zmk_widget_halo_hud *widget, lv_obj_t *parent) {
    widget->obj = lv_obj_create(parent);
    lv_obj_set_size(widget->obj, 64, 32);
    lv_obj_add_event_cb(widget->obj, (lv_event_cb_t)draw_halo_frame, LV_EVENT_DRAW_MAIN, NULL);
    lv_obj_clear_flag(widget->obj, LV_OBJ_FLAG_SCROLLABLE);

    add_ui_elements(widget);

    // Set up WPM update callback
    zmk_widget_wpm_status_init(&widget->wpm_status, widget, hud_update_cb);
    
    return 0;
}

lv_obj_t *zmk_widget_halo_hud_obj(struct zmk_widget_halo_hud *widget) {
    return widget->obj;
}