#include "vgpio.h"
#include <stddef.h>

//tüm registerler 0 olmalı
vgpio_status_t vgpio_init(vgpio_t *port){

    if (port == NULL)
    {
        return VGPIO_ERR_NULL;
    }
    port->MODER = 0u;
    port->ODR = 0u;
    port->IDR = 0u;

}


//pinin modunu yazcaz 
vgpio_status_t vgpio_set_mode(vgpio_t *port, uint8_t pin, vgpio_mode_t mode){
if (port == NULL)
{
    return VGPIO_ERR_NULL;
}

if (pin >= VGPIO_PIN_COUNT)
{
    return VGPIO_ERR_PIN;
}

uint32_t shift = pin*2u;

port->MODER &=~(0x3u << shift); //istediğim alanı sıfırladım

port->MODER |= ((uint32_t)mode << shift); //güvenli olması için burda tip belirttik 

return VGPIO_OK;
}

vgpio_status_t vgpio_get_mode(const vgpio_t *port, uint8_t pin, vgpio_mode_t *out){

if (port == NULL || out == NULL)
{
    return VGPIO_ERR_NULL;
}

if (pin >= VGPIO_PIN_COUNT)
{
    return VGPIO_ERR_PIN;
}


uint32_t shift = pin*2u;
*out = (vgpio_mode_t)((port->MODER >> shift) & 0x3u);
return VGPIO_OK;

}



/* Pin cikis modundaysa ODR'nin n. bitini level (0/1) yapar */
vgpio_status_t vgpio_write(vgpio_t *port, uint8_t pin, uint8_t level){

if (port == NULL)
{
    return VGPIO_ERR_NULL;
}

if (pin >= VGPIO_PIN_COUNT)
{
    return VGPIO_ERR_PIN;
}

uint32_t shift = pin*2u;
vgpio_mode_t mode = (vgpio_mode_t)((port->MODER >> shift) & 0x3u);

if (mode != VGPIO_MODE_OUTPUT)
{
    return VGPIO_ERR_NOT_OUTPUT;
}


//0 sa kapat
if (level == 0u)
{
    port->ODR &= ~(1u<<pin);
    
}else{
    port->ODR |= (1u<<pin);

}

return VGPIO_OK;
}



/* Pin cikis modundaysa ODR'nin n. bitini ters cevirir */
vgpio_status_t vgpio_toggle(vgpio_t *port, uint8_t pin){
if (port == NULL)
{
    return VGPIO_ERR_NULL;
}

if (pin >= VGPIO_PIN_COUNT)
{
    return VGPIO_ERR_PIN;
}

uint32_t shift = pin*2u;
vgpio_mode_t mode = (vgpio_mode_t)((port->MODER >> shift) & 0x3u);

if (mode != VGPIO_MODE_OUTPUT)
{
    return VGPIO_ERR_NOT_OUTPUT;
}

port->ODR ^= (1u<<pin);

return VGPIO_OK;


}


/* IDR'nin n. bitini okur */
vgpio_status_t vgpio_read(const vgpio_t *port, uint8_t pin, uint8_t *out){

if (port == NULL || out == NULL)
{
    return VGPIO_ERR_NULL;
}

if (pin >= VGPIO_PIN_COUNT)
{
    return VGPIO_ERR_PIN;
}

*out = (port->IDR>>pin) & 1u;
return VGPIO_OK;


}