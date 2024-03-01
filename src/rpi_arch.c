#include <stdint.h>
#include "rpi_arch.h"


void delay(uint32_t val)
{
	while (val > 0)
	{
		val--;
	}
}


void uart_putc(char c)
{
	/* Wait until UART ready */
	while ( regRead32(UART0_FR) & (1 << 5));
	/* Write character */
	regWrite32(UART0_DR, c);
}

