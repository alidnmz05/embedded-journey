#include "bitops.h"

uint8_t bit_set(uint8_t reg, uint8_t n)
{

return reg | (1u << n);

}

uint8_t bit_clear(uint8_t reg, uint8_t n){

    return reg &~(1u << n);

}


uint8_t bit_toggle(uint8_t reg, uint8_t n){

return reg ^ (1u << n);

}

uint8_t bit_read(uint8_t reg, uint8_t n){

    return (reg >> n) & 1;

}