#include <stdint.h>
#include "rpi_arch.h"
#include "utils.h"
#include "dlsh.h"
#include "shell_commands.h"


#define BLINK_FREQ				1000000		/* 1 sec */


void blink(void);
static int shellStart(void);


/**
*	C entry point
*/
void entryC(void)
{
	printStr("\r\n============");
	printStr("\r\nHello World!");
	printStr("\r\n============\r\n\r\n");

	/* Register DLSH commands */
	shRegisterCommands();

	/* Start blink loop */
	blink();
}


static int shellStart(void)
{
	/* Check for key press */
	if (uartInputReady())
	{
		/* Flush */
		uartGetC();
		
		/* Start shell */
		dlshStart(printStr, uartGetC, 1);

		return 1;
	}

	return 0;
}


void blink(void)
{
	uint32_t i = 0;
	uint64_t prevSysTime = 0;
	uint64_t currSysTime = 0;

	/* Set GPIO 47 as output (Activity LED) */
	gpioFselSet(47, GPIO_FSEL_OUTPUT);

	printStr("Start blink @ ");
	printValDec(BLINK_FREQ, "", " Hz (press any key to exit)\r\n\n");

	while (1)
	{
		if (shellStart())
		{
			return;
		}

		/* Set GPIO 47 */
		gpioValSet(47, GPIO_VAL_ON);

		/* Delay */
		sysTimerDelay(BLINK_FREQ);

		/* Clear GPIO 47 */
		gpioValSet(47, GPIO_VAL_OFF);

		if (shellStart())
		{
			return;
		}

		/* Delay */
		sysTimerDelay(BLINK_FREQ);

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


