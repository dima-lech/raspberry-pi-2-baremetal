#include <stdint.h>
#include "rpi_arch.h"



extern void do_nothing();
void blink(void);
void uart_putc(char c);
void print_str(char * str);



/**
*	C entry point
*/
void entry_c(void)
{
	/* print_str("\r\nHello World!\r\n\r\n"); */

	blink();
}


void uart_putc(char c)
{
	/* Wait until UART ready */
	while ( regRead32(UART0_FR) & (1 << 5));
	/* Write character */
	regWrite32(UART0_DR, c);
}


void blink(void)
{
	uint32_t regVal32;

	regVal32 = regRead32(GPFSEL4);
	regVal32 &= ~(7 << 21);
	regVal32 |= 1 << 21;
	regWrite32(GPFSEL4, regVal32);

	while (1)
	{
		/* Set bit */
		regWrite32(GPSET1, 1 << (47 - 32));

		/* delay */
		delay(1000000);

    	/* Clear bit */
    	regWrite32(GPCLR1, 1 << (47 - 32));

		/* delay */
		delay(1000000);

		/* Print '.' character to UART */
		uart_putc('.');
	}
}


void print_str(char * str)
{
	if (0 == str)
	{
		return;
	}

	while (*str != '\0')
	{
		uart_putc(*str);
		str++;
	}
}

