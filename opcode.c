

#include <stdint.h>
#include <stddef.h>
#include <assert.h>
#ifndef WAYLAND_STUFF_H
#define WAYLAND_STUFF_H
static const uint32_t  wayland_display_object_id= 1;

 static const uint16_t wayland_wl_registry_event_global = 0;

 static const uint16_t wayland_shm_pool_event_format = 0;

 static const uint16_t wayland_wl_buffer_event_release = 0;

 static const uint16_t wayland_xdg_wm_base_event_ping = 0;

 static const uint16_t wayland_xdg_toplevel_event_configure = 0;

 static const uint16_t wayland_xdg_toplevel_event_close = 1;

 static const uint16_t wayland_xdg_surface_event_configure = 0;

 static const uint16_t wayland_wl_display_get_registry_opcode = 1;

 static const uint16_t wayland_wl_registry_bind_opcode = 0;

 static const uint16_t wayland_wl_compositor_create_surface_opcode = 0;

 static const uint16_t wayland_xdg_wm_base_pong_opcode = 3;

 static const uint16_t wayland_xdg_surface_ack_configure_opcode = 4;

 static const uint16_t wayland_wl_shm_create_pool_opcode = 0;

 static const uint16_t wayland_xdg_wm_base_get_xdg_surface_opcode = 2;

 static const uint16_t wayland_wl_shm_pool_create_buffer_opcode = 0;

 static const uint16_t wayland_wl_surface_attach_opcode = 1;

 static const uint16_t wayland_xdg_surface_get_toplevel_opcode = 1;

 static const uint16_t wayland_wl_surface_commit_opcode = 6;

 static const uint16_t wayland_wl_display_error_event = 0;

 static const uint32_t wayland_format_xrgb8888 = 1;

 static const uint32_t wayland_header_size = 8;

 static const uint32_t color_channels = 4;

 enum state_state_t {

   STATE_NONE,

   STATE_SURFACE_ACKED_CONFIGURE,

   STATE_SURFACE_ATTACHED,

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
#endif