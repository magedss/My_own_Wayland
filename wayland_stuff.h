#ifndef WAYLAND_STUFF_H
#define WAYLAND_STUFF_H

#include <stdint.h>

// Constant declarations
extern const uint32_t wayland_display_object_id;
extern const uint16_t wayland_wl_registry_event_global;
extern const uint16_t wayland_shm_pool_event_format;
extern const uint16_t wayland_wl_buffer_event_release;
extern const uint16_t wayland_xdg_wm_base_event_ping;
extern const uint16_t wayland_xdg_toplevel_event_configure;
extern const uint16_t wayland_xdg_toplevel_event_close;
extern const uint16_t wayland_xdg_surface_event_configure;
extern const uint16_t wayland_wl_display_get_registry_opcode;
extern const uint16_t wayland_wl_registry_bind_opcode;
extern const uint16_t wayland_wl_compositor_create_surface_opcode;
extern const uint16_t wayland_xdg_wm_base_pong_opcode;
extern const uint16_t wayland_xdg_surface_ack_configure_opcode;
extern const uint16_t wayland_wl_shm_create_pool_opcode;
extern const uint16_t wayland_xdg_wm_base_get_xdg_surface_opcode;
extern const uint16_t wayland_wl_shm_pool_create_buffer_opcode;
extern const uint16_t wayland_wl_surface_attach_opcode;
extern const uint16_t wayland_xdg_surface_get_toplevel_opcode;
extern const uint16_t wayland_wl_surface_commit_opcode;
extern const uint16_t wayland_wl_display_error_event;
extern const uint32_t wayland_format_xrgb8888;
extern const uint32_t wayland_header_size;
extern const uint32_t color_channels;
 #define roundup_4(n) (((n) + 3) & -4)
enum state_state_t {
    STATE_NONE,
    STATE_SURFACE_ACKED_CONFIGURE,
    STATE_SURFACE_ATTACHED
};

struct state_t {
    uint32_t wl_registry;
    uint32_t wl_shm;
    uint32_t wl_shm_pool;
    uint32_t wl_buffer;
    uint32_t xdg_wm_base;
    uint32_t xdg_surface;
    uint32_t wl_compositor;
    uint32_t wl_surface;
    uint32_t xdg_toplevel;
    uint32_t stride;
    uint32_t w;
    uint32_t h;
    uint32_t shm_pool_size;
    int shm_fd;
    uint8_t *shm_pool_data;
    enum state_state_t state;
};

#endif /