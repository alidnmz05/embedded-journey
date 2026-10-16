#include "ring_buffer.h"


rb_status_t rb_init(ring_buffer_t *rb) {
    if (rb == NULL){
        return RB_ERR_NULL;
    }
    rb->head = 0;
    rb->tail = 0;
    return RB_OK;
}

rb_status_t rb_push(ring_buffer_t *rb, uint8_t byte) {
if (rb == NULL)
{
    return RB_ERR_NULL;
}

if(rb_is_full(rb))
{
    return RB_ERR_FULL;
}

rb->data[rb->head] = byte;
rb->head = (rb->head + 1) & (RB_CAPACITY - 1);
return RB_OK;
}

rb_status_t rb_pop(ring_buffer_t *rb, uint8_t *out){
if(rb == NULL || out == NULL)
{
    return RB_ERR_NULL;
}

if(rb_is_empty(rb)){

    return RB_ERR_EMPTY;
}

*out = rb->data[rb->tail];
rb->tail = (rb->tail+1) & (RB_CAPACITY-1);

return RB_OK;

}

bool rb_is_empty(const ring_buffer_t *rb){
if(rb->head == rb->tail)
{
    return true;
}
else {
    return false;
}
}


size_t rb_count(const ring_buffer_t *rb)
{
    if (rb == NULL)
    {
        return 0;
    }

    return (rb->head - rb->tail) & (RB_CAPACITY - 1);
}

bool rb_is_full(const ring_buffer_t *rb){
    if(rb_count(rb) == (RB_CAPACITY-1)){
       return true;
    } else return false;
}



