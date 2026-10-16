#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/* Kapasite 2'nin kuvveti olmak zorunda (ör. 8, 16, 64, 256).
 * Sebep: sarma islemini modulo yerine bitmask ile yapacagiz. */
#define RB_CAPACITY 8u

typedef struct {
    uint8_t  data[RB_CAPACITY];
    volatile size_t head;   /* bir sonraki yazilacak indeks */
    volatile size_t tail;   /* bir sonraki okunacak indeks  */
} ring_buffer_t;

typedef enum {
    RB_OK = 0,
    RB_ERR_NULL,    /* NULL pointer verildi */
    RB_ERR_FULL,    /* yazarken tampon doluydu */
    RB_ERR_EMPTY    /* okurken tampon bosdu */
} rb_status_t;

/* Tamponu bosaltir ve baslangic durumuna getirir. */
rb_status_t rb_init(ring_buffer_t *rb);

/* Tek bayt yazar. Doluysa RB_ERR_FULL doner, veri yazilmaz. */
rb_status_t rb_push(ring_buffer_t *rb, uint8_t byte);

/* Tek bayt okur ve *out icine koyar. Bossa RB_ERR_EMPTY doner. */
rb_status_t rb_pop(ring_buffer_t *rb, uint8_t *out);

/* Tamponda okunmayi bekleyen bayt sayisi. */
size_t rb_count(const ring_buffer_t *rb);

/* true: bos, false: bos degil. */
bool rb_is_empty(const ring_buffer_t *rb);

/* true: dolu, false: dolu degil. */
bool rb_is_full(const ring_buffer_t *rb);

#endif /* RING_BUFFER_H */