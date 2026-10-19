CC      = arm-none-eabi-gcc
CFLAGS  = -mcpu=cortex-m7 -mthumb -Wall -Wextra -g
LDFLAGS = -nostdlib -T linker.ld

led.elf: startup.c main.c linker.ld
	$(CC) $(CFLAGS) $(LDFLAGS) startup.c main.c -o led.elf

flash: led.elf
	openocd -f interface/stlink.cfg -f target/stm32h7x.cfg -c "program led.elf verify reset exit"

clean:
	rm -f led.elf