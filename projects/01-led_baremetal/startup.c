#include <stdint.h>


extern int main(void);

#define STACK_TOP 0x20020000u

void Reset_Handler(void)
{
    main();
    while (1)
    {
        /* code */
    }
    
}

/* Vektor tablosu: flash'in basina (0x08000000) yerlesecek */
__attribute__((section(".vectors")))
const uint32_t vector_table[] = {
    STACK_TOP,                   /* 0x08000000: baslangic SP */
    (uint32_t)Reset_Handler      /* 0x08000004: reset sonrasi PC */
};