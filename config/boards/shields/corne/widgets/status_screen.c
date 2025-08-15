
#include <zmk/display/status_screen.h>
#include "widgets/halo_hud.h"

#if IS_ENABLED(CONFIG_ZMK_DISPLAY_STATUS_SCREEN_CUSTOM)

static struct zmk_widget_halo_hud halo_widget;

lv_obj_t *zmk_display_status_screen() {
    lv_obj_t *screen;
    screen = lv_obj_create(NULL, NULL);

    zmk_widget_halo_hud_init(&halo_widget, screen);
    lv_obj_align(zmk_widget_halo_hud_obj(&halo_widget), NULL, LV_ALIGN_CENTER, 0, 0);

    return screen;
}

#endif // IS_ENABLED(CONFIG_ZMK_DISPLAY_STATUS_SCREEN_CUSTOM)