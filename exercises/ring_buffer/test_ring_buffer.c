#include <stdio.h>
#include "ring_buffer.h"

int main(void)
{
    ring_buffer_t rb;
    uint8_t x;

    rb_init(&rb);

    for (uint8_t i = 1; i <= 8; i++)
    {
        rb_status_t s = rb_push(&rb, i);
        printf("push %u -> durum %d, sayi %zu\n", i, s, rb_count(&rb));
    }

    while (rb_pop(&rb, &x) == RB_OK)
    {
        printf("pop -> %u\n", x);
    }

    return 0;
}