#include <stdio.h>
#include "bitops.h"

int main(void)
{
    uint8_t reg = 0;

    reg = bit_set(reg, 2);
    printf("2. bit acildi: %u\n", reg);   /* beklenen 4 */

    reg = bit_set(reg, 5);
    printf("5. bit acildi: %u\n", reg);   /* beklenen 36 */

    reg = bit_clear(reg, 2);
    printf("2. bit kapandi: %u\n", reg);  /* beklenen 32 */

    reg = bit_toggle(reg, 5);
    printf("5. bit ters: %u\n", reg);     /* beklenen 0 */

    printf("read(6, 2) = %u\n", bit_read(6, 2));  /* beklenen 1 */

    return 0;
}