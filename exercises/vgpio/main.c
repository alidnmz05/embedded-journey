#include <stdio.h>
#include "vgpio.h"

int main(void)
{
    vgpio_t port;
    vgpio_mode_t m;
    uint8_t lvl;

    vgpio_init(&port);

    vgpio_set_mode(&port, 5, VGPIO_MODE_OUTPUT);
    printf("MODER = 0x%X (beklenen 0x400)\n", port.MODER);

    vgpio_set_mode(&port, 3, VGPIO_MODE_ALT);
    printf("MODER = 0x%X (beklenen 0x480)\n", port.MODER);

    vgpio_get_mode(&port, 5, &m);
    printf("pin 5 modu = %d (beklenen 1)\n", m);

    printf("write(5,1) -> %d, ODR = 0x%X (beklenen 0, 0x20)\n",
           vgpio_write(&port, 5, 1), port.ODR);

    printf("toggle(5)  -> %d, ODR = 0x%X (beklenen 0, 0x0)\n",
           vgpio_toggle(&port, 5), port.ODR);

    printf("write(3,1) -> %d (beklenen %d, cunku pin 3 cikis degil)\n",
           vgpio_write(&port, 3, 1), VGPIO_ERR_NOT_OUTPUT);

    printf("write(16,1) -> %d (beklenen %d)\n",
           vgpio_write(&port, 16, 1), VGPIO_ERR_PIN);

    port.IDR = 0x1;   /* butona basildi simulasyonu: pin 0 */
    vgpio_read(&port, 0, &lvl);
    printf("read(0) = %u (beklenen 1)\n", lvl);

    return 0;
}