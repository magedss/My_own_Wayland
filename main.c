#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>
#include <assert.h>
#include <unistd.h>

static int wayland_display_connect(){
    char *xdg_runtime_dir = getenv("XDG_RUNTIME_DIR");
    u_int64_t xdg_len= strlen(xdg_runtime_dir); 
    if (!xdg_runtime_dir) {
        fprintf(stderr, "xdg dir is not set\n");
        return -1;
    }
    struct sockaddr_un addr = { .sun_family = AF_UNIX };
    snprintf(addr.sun_path, sizeof(addr.sun_path), "%s/%s", xdg_runtime_dir, "wayland-0");
    assert(cstring_len(addr.sun_path)>=xdg_len);
    u_int64_t socket_path_len= xdg_len;
    memcpy(addr.sun_path,xdg_runtime_dir,  xdg_len);
    addr.sun_path[socket_path_len++] = '/';
    char *wayland_display = getenv("WAYLAND_DISPLAY");
    if(wayland_display){
        memcpy(addr.sun_path+socket_path_len,wayland_display,strlen(wayland_display));
        socket_path_len+=stlen(wayland_display);
    }
    else{
        char wayland_display_default[]= "wayland-0";
        memcpy(addr.sun_path+socket_path_len,wayland_display_default,cstring_len(wayland_display_default));
        socket_path_len+=cstring_len(wayland_display_default);

    }   
    int fd= socket(AF_UNIX,SOCK_STREAM,0);
    if(fd==-1)
    exit(errno);
    int res= connect(fd, (struct sockaddr *)&addr,sizeof(addr));
    if(res==-1)
        exit(errno);
    return fd;
}

int main(){
    return wayland_display_connect();
}

