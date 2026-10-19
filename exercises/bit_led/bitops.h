#ifndef BITOPS_H
#define BITOPS_H

#include <stdint.h>

/* n. biti 1 yapar */
uint8_t bit_set(uint8_t reg, uint8_t n);

/* n. biti 0 yapar */
uint8_t bit_clear(uint8_t reg, uint8_t n);

/* n. biti ters cevirir */
uint8_t bit_toggle(uint8_t reg, uint8_t n);

/* n. bitin degerini dondurur (0 veya 1) */
uint8_t bit_read(uint8_t reg, uint8_t n);

/* reg'i ekrana "0000 0101" ve "●○●○..." seklinde basar */
void leds_print(uint8_t reg);

#endif /* BITOPS_H */