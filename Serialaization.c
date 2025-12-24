
#include <stdint.h>
#include <stddef.h>
#include <assert.h>

static void buf_write_u32(char *buffer, uint64_t *buf_size, uint64_t buf_capacity,uint32_t x){
    assert(*buf_size + sizeof(x) <= buf_capacity);
    assert(((*buf_size) + (size_t)buffer) % sizeof(x) == 0);
   *(uint32_t *)(buffer+ (*buf_size))=x;
    *buf_size+=sizeof(x);

} 
static void buf_write_u16(char *buffer, uint64_t *buf_size, uint64_t buf_capacity,uint16_t x){
    assert(*buf_size + sizeof(x) <= buf_capacity);
    assert(((*buf_size) + (size_t)buffer) % sizeof(x) == 0);
   *(uint32_t *)(buffer+ (*buf_size))=x;
    *buf_size+=sizeof(x);

} 
static uint32_t buf_read_u32(char **buffer, uint64_t *buf_size){
    assert(((size_t)*buffer%sizeof(uint32_t))==0);
    assert(*buf_size>=sizeof(uint32_t));
    uint32_t result= *(uint32_t*)*buffer;
    *buffer+=sizeof(result);
    *buf_size-=sizeof(result);
    return result;

}
