#include <stdint.h>
#include "rpi_arch.h"


void delay(uint32_t val)
{
	while (val > 0)
	{
		val--;
	}
}


void uartPutC(char c)
{
	/* Wait until UART ready */
	while (regRead32(UART0_FR) & (1 << 5));
	/* Write character */
	regWrite32(UART0_DR, c);
}


uint64_t sysTimerGet(void)
{
	uint32_t lo;
	uint32_t hi;
	uint32_t flagOk = 0;
	uint64_t result;

	do
	{
		hi = regRead32(SYS_TIMER_CHI);
		lo = regRead32(SYS_TIMER_CLO);

		if (regRead32(SYS_TIMER_CHI) == hi)
		{
			flagOk = 1;
		}
	} while (0 == flagOk);

	result = ((uint64_t)hi << 32) | lo;

	return result;
}

