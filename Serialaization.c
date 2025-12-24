
#include <stdint.h>
#include <stddef.h>
#include <assert.h>

static void buf_write_u32(char *buffer, uint64_t *buf_size, uint64_t buf_capacity,uint32_t x){
    assert(*buf_size + sizeof(x) <= buf_capacity);
    assert(((*buf_size) + (size_t)buffer) % sizeof(x) == 0);

} 