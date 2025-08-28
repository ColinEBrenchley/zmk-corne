target_sources(app PRIVATE 
    halo_hud.c
    status_screen.c
)

target_include_directories(app PRIVATE 
    .
    ${ZEPHYR_BASE}/include
    ${ZMK_BASE}/include
    ${LVGL_BASE}/include
)

target_link_libraries(app PRIVATE zmk_display)