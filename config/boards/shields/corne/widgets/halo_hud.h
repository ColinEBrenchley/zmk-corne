#pragma once

#include <zephyr/kernel.h>
#include <zmk/display.h>
#include <lvgl.h>

#include <zmk/wpm.h>
#include <zmk/display/widgets/wpm_status.h>
#include <zmk/events/wpm_state_changed.h>
#include <zmk/events/battery_state_changed.h>

struct zmk_widget_halo_hud {
    sys_snode_t node;
    lv_obj_t *obj;
    lv_obj_t *wpm_label;
    lv_obj_t *battery_label;
    lv_obj_t *bluetooth_label;
    struct zmk_widget_wpm_status wpm_status;
};

int zmk_widget_halo_hud_init(struct zmk_widget_halo_hud *widget, lv_obj_t *parent);
lv_obj_t *zmk_widget_halo_hud_obj(struct zmk_widget_halo_hud *widget);