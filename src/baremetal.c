#include <stdint.h>
#include "rpi_arch.h"
#include "utils.h"
#include "dlsh.h"


#undef	DLSH_ENABLE

#define BLINK_FREQ		1000000		/* 1 sec */


void blink(uint32_t freq);


/**
*	C entry point
*/
void entryC(void)
{
	printStr("\r\n============");
	printStr("\r\nHello World!");
	printStr("\r\n============\r\n\r\n");

#ifdef	DLSH_ENABLE
	dlshStart(printStr, uartGetC, 1);
#endif

	blink(BLINK_FREQ);
}


void blink(uint32_t freq)
{
	uint32_t i = 0;
	uint64_t prevSysTime = 0;
	uint64_t currSysTime = 0;

	/* Set GPIO 47 as output (Activity LED) */
	gpioFselSet(47, GPIO_FSEL_OUTPUT);

	printStr("Start blink @ ");
	printValDec(freq, "", " Hz\r\n\r\n");

	while (1)
	{
		/* Set GPIO 47 */
		gpioValSet(47, GPIO_VAL_ON);

		/* Delay */
		sysTimerDelay(freq);

		/* Clear GPIO 47 */
		gpioValSet(47, GPIO_VAL_OFF);

		/* Delay */
		sysTimerDelay(freq);

		currSysTime = sysTimerGet();
		printStr("System timer = ");
		printValHex(currSysTime, 16, "0x", "");
		if (i > 0)
		{
			printStr("\t(delta ");
			printValDec((uint32_t)(currSysTime - prevSysTime), "", "");
			printStr(")");
		}
		printStr("\r\n");
		prevSysTime = currSysTime;

		i++;
	}
}


