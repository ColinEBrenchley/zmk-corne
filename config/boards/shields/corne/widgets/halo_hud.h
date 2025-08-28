#pragma once

#include <zephyr/kernel.h>
#include <lvgl.h>
#include <zmk/display.h>
#include <zmk/events/wpm_state_changed.h>
#include <zmk/wpm.h>
#include <zmk/events/battery_state_changed.h>
#include <zmk/events/ble_active_profile_changed.h>

struct zmk_widget_halo_hud {
    sys_snode_t node;
    lv_obj_t *obj;
    lv_obj_t *wpm_label;
    lv_obj_t *battery_label;
    lv_obj_t *bluetooth_label;
};

int zmk_widget_halo_hud_init(struct zmk_widget_halo_hud *widget, lv_obj_t *parent);
lv_obj_t *zmk_widget_halo_hud_obj(struct zmk_widget_halo_hud *widget);