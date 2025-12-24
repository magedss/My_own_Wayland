#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>
#include <assert.h>
#include <unistd.h>
#include "wayland_stuff.h"

 static uint32_t wayland_current_id = 1;
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
static uint32_t wayland_wl_display_get_registry(int fd){
    uint64_t msg_len=0;
    char msg [128]="";
    buf_write_u32(msg,&msg_len,sizeof(msg_len),wayland_display_object_id);
    buf_write_u16(msg, &msg_size, sizeof(msg),wayland_wl_display_get_registry_opcode);
    buf_write_u16(msg, &msg_size, sizeof(msg),wayland_header_size+sizeof(wayland_current_id));
    wayland_current_id++;
    buf_write_u32(msg, &msg_size, sizeof(msg), wayland_current_id);
    send(fd,msg,msg_len,MSG_DONTWAIT);
    printf("-> wl_display@%u.get_registry: wl_registry=%u\n",
    wayland_display_object_id, wayland_current_id);

   return wayland_current_id;
}
static void generate_name(char *name){
    for(uint64_t i = 1 ; i < cstring(name);i++){
       name[i]= ((double)rand())/(double)RAND_MAX*26+'a';
    }
}
static void create_shared_memory(uint64_t size, struct state_t *state ){
    char name[255]="/";
    generate_name(name);
   int fd = shm_open(name, O_RDWR | O_EXCL | O_CREAT, 0600);
    if(fd!=-1&&shm_unlink(name)!=-1&&ftruncate(fd,size)!=-1){
        state.shm_pool_date =mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
        assert(state.shm_pool_data==NULL);
        state.shm_fd=fd;

    }
    else
        exit(errno);
    

}
int main(){
    return wayland_display_connect();
}

