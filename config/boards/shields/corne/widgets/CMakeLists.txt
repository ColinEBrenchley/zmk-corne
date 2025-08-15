target_sources_ifdef(CONFIG_ZMK_DISPLAY_STATUS_SCREEN_CUSTOM app PRIVATE
    halo_hud.c
    status_screen.c
)

target_include_directories_ifdef(CONFIG_ZMK_DISPLAY app PRIVATE 
    .
)

target_include_directories(app PRIVATE 
    ${ZEPHYR_BASE}/include
    ${ZMK_BASE}/include
    ${LVGL_BASE}/include
)

target_link_libraries(app PRIVATE zmk_display)