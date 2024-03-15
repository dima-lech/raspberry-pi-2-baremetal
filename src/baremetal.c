#include <stdint.h>
#include "rpi_arch.h"
#include "utils.h"
#include "dlsh.h"


#define BLINK_FREQ				1000000		/* 1 sec */


static void blink(uint32_t freq);
static void blinkCommand(int argc, char * argv[]);
static void ledCommand(int argc, char * argv[]);
static int shellStart(void);


/**
*	C entry point
*/
void entryC(void)
{
	printStr("\r\n============");
	printStr("\r\nHello World!");
	printStr("\r\n============\r\n\r\n");

	dlshRegisterCommand("blink", blinkCommand);
	dlshRegisterCommand("led", ledCommand);

	blink(BLINK_FREQ);
}


void blinkCommand(__attribute__((unused)) int argc, __attribute__((unused)) char * argv[])
{
	dlshExit();
	blink(BLINK_FREQ);
}

void ledCommand(int argc, char * argv[])
{
	if ((argc > 1) && (strcmp(argv[1], "on")))
	{
		printStr("LED: on\r\n");
		gpioValSet(47, GPIO_VAL_ON);
	}
	else if ((argc > 1) && (strcmp(argv[1], "off")))
	{
		printStr("LED: off\r\n");
		gpioValSet(47, GPIO_VAL_OFF);
	}
	else
	{
		printStr("usage: ");
		printStr(argv[0]);
		printStr(" <on|off>\r\n");
	}
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


static void blink(uint32_t freq)
{
	uint32_t i = 0;
	uint64_t prevSysTime = 0;
	uint64_t currSysTime = 0;

	/* Set GPIO 47 as output (Activity LED) */
	gpioFselSet(47, GPIO_FSEL_OUTPUT);

	printStr("Start blink @ ");
	printValDec(freq, "", " Hz (press any key to exit)\r\n\n");

	while (1)
	{
		if (shellStart())
		{
			return;
		}

		/* Set GPIO 47 */
		gpioValSet(47, GPIO_VAL_ON);

		/* Delay */
		sysTimerDelay(freq);

		/* Clear GPIO 47 */
		gpioValSet(47, GPIO_VAL_OFF);

		if (shellStart())
		{
			return;
		}

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


