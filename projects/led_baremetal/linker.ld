MEMORY
{
    FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 2M
    RAM   (rwx) : ORIGIN = 0x20000000, LENGTH = 128K
}

ENTRY(Reset_Handler)

SECTIONS
{
    .text :
    {
        KEEP(*(.vectors))   /* once vektor tablosu: 0x08000000'a duser */
        *(.text*)           /* sonra butun kodlar */
        *(.rodata*)         /* sonra sabitler (const veriler) */
    } > FLASH
}