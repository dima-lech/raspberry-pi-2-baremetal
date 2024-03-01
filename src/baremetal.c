#include <stdint.h>

#define GPFSEL4 0x3F200010
#define GPSET1 0x3F200020
#define GPCLR1 0x3F20002C

#define UARTDR	0x3F201000

extern void do_nothing();
void blink(void);
void uart_putc(char c);


void entry_c(void)
{
	blink();
}


void uart_putc(char c)
{
	*(unsigned int *)UARTDR = c;
}


void blink(void)
{
	*(volatile uint32_t *)GPFSEL4 &= ~(7 << 21);
	*(volatile uint32_t *)GPFSEL4 |= 1 << 21;

	while (1)
	{
		*(volatile uint32_t *)GPSET1 = 1 << (47 - 32);

		for (uint32_t i = 0; i < 0x100000; i++)
		{
			do_nothing();
    	}

		*(volatile uint32_t *)GPCLR1 = 1 << (47 - 32);

		for (uint32_t i = 0; i < 0x100000; i++)
		{
			do_nothing();
		}

		uart_putc('.');
	}
}
