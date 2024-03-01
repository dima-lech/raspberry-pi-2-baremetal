#include <stdint.h>
#include "rpi_arch.h"
#include "utils.h"



void blink(void);



/**
*	C entry point
*/
void entry_c(void)
{
	print_str("\r\nHello World!\r\n");

	blink();
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


