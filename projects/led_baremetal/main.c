#include <stdint.h>



typedef struct
{
    volatile uint32_t MODER;    /* 0x00 */
    volatile uint32_t OTYPER;   /* 0x04 */
    volatile uint32_t OSPEEDR;  /* 0x08 */
    volatile uint32_t PUPDR;    /* 0x0C */
    volatile uint32_t IDR;      /* 0x10 */
    volatile uint32_t ODR;      /* 0x14 */
} gpio_t;

typedef struct
{
    gpio_t *port;
    uint8_t pin;
} led_t;

#define GPIOB ((gpio_t *)0x58020400u) // b'nin baseini tanımladık
#define GPIOE ((gpio_t *)0x58021000u) // e'nin baseini tanımladık
#define RCC_AHB4ENR   (*(volatile uint32_t *)0x580244E0u)


static const led_t LD1 = { GPIOB, 0  };
static const led_t LD2 = { GPIOE, 1  };
static const led_t LD3 = { GPIOB, 14 };



// Bare-metal için basit yazılımsal gecikme fonksiyonu
// __attribute__((noinline)) derleyicinin bu döngüyü optimize edip silmesini engeller
__attribute__((noinline)) void delay(volatile uint32_t count)
{
    while (count--)
    {
        __asm("nop"); // İşlemciyi boş bir döngüde tutar
    }
}


void clock_enable_gpio(uint8_t port_index)
{
    RCC_AHB4ENR |= (1u << port_index);
}


void gpio_set_output(gpio_t * gpio, uint8_t pin)
{
    gpio->MODER &= ~(3u << pin*2); 
    gpio->MODER |= (1u << pin*2); //moderı 01 yaptım
    
}



int main(void)
{
    clock_enable_gpio(1);
    clock_enable_gpio(4);


    gpio_set_output(GPIOB, 14);
    gpio_set_output(GPIOB, 0);
    gpio_set_output(GPIOE, 1);
    
     while (1)
    {   

        //1. yi yak
        GPIOB->ODR |= (1u << 14);
        delay(4000000); // Yaklaşık bir gecikme 
        GPIOB->ODR &= ~(1u << 14);

        GPIOE->ODR |= (1u << 1);
        delay(4000000); // Yaklaşık bir gecikme 
        GPIOE->ODR &= ~(1u << 1);
      
        GPIOB->ODR |= (1u << 0);
        delay(4000000); // Yaklaşık bir gecikme 
        GPIOB->ODR &= ~(1u << 0);
        
    }
}

