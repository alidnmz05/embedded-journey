#ifndef VGPIO_H
#define VGPIO_H

#include <stdint.h>

#define VGPIO_PIN_COUNT 16u

/* Her pinin modu MODER icinde 2 bit yer kaplar */
typedef enum {
    VGPIO_MODE_INPUT  = 0u,   /* 00 */
    VGPIO_MODE_OUTPUT = 1u,   /* 01 */
    VGPIO_MODE_ALT    = 2u,   /* 10 */
    VGPIO_MODE_ANALOG = 3u    /* 11 */
} vgpio_mode_t;

typedef enum {
    VGPIO_OK = 0,
    VGPIO_ERR_NULL,
    VGPIO_ERR_PIN,        /* pin 0-15 disinda */
    VGPIO_ERR_NOT_OUTPUT  /* cikis olmayan pine yazilmaya calisildi */
} vgpio_status_t;

/* Sanal port: gercek STM32'deki register'larin kucuk bir modeli */
typedef struct {
    uint32_t MODER;   /* pin n -> bit (2n+1 : 2n), mod secimi */
    uint32_t ODR;     /* pin n -> bit n, cikis seviyesi       */
    uint32_t IDR;     /* pin n -> bit n, giris seviyesi       */
} vgpio_t;

/* Tum register'lari 0 yapar (tum pinler giris) */
vgpio_status_t vgpio_init(vgpio_t *port);

/* Pinin modunu MODER icindeki 2 bitlik alana yazar */
vgpio_status_t vgpio_set_mode(vgpio_t *port, uint8_t pin, vgpio_mode_t mode);

/* Pinin modunu MODER'den okur */
vgpio_status_t vgpio_get_mode(const vgpio_t *port, uint8_t pin, vgpio_mode_t *out);

/* Pin cikis modundaysa ODR'nin n. bitini level (0/1) yapar */
vgpio_status_t vgpio_write(vgpio_t *port, uint8_t pin, uint8_t level);

/* Pin cikis modundaysa ODR'nin n. bitini ters cevirir */
vgpio_status_t vgpio_toggle(vgpio_t *port, uint8_t pin);

/* IDR'nin n. bitini okur */
vgpio_status_t vgpio_read(const vgpio_t *port, uint8_t pin, uint8_t *out);

/* Portu 16 pin icin "pin: mod, seviye" seklinde ekrana basar */
void vgpio_print(const vgpio_t *port);

#endif /* VGPIO_H */