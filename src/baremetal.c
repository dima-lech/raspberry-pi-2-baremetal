#include <stdint.h>
#include "rpi_arch.h"
#include "utils.h"
#include "dlsh.h"


#define	DLSH_ENABLE

#define BLINK_FREQ				1000000		/* 1 sec */
#define SHELL_START_TIMEOUT		5000000		/* 5 sec */


void blink(uint32_t freq);
void blinkCommand(int argc, char * argv[]);
void ledCommand(int argc, char * argv[]);


/**
*	C entry point
*/
void entryC(void)
{
#ifdef	DLSH_ENABLE
	int keyPressed = 0;
#endif

	printStr("\r\n============");
	printStr("\r\nHello World!");
	printStr("\r\n============\r\n\r\n");

#ifdef	DLSH_ENABLE
	printValDec(SHELL_START_TIMEOUT / 1000000, "Waiting for key press in ", " seconds...\n");
	while (sysTimerGet() < SHELL_START_TIMEOUT)
	{
		if (uartInputReady())
		{
			/* Flush */
			uartGetC();
			keyPressed = 1;
			break;
		}
	}

	if (keyPressed)
	{
		dlshRegisterCommand("blink", blinkCommand);
		dlshRegisterCommand("led", ledCommand);
		dlshStart(printStr, uartGetC, 1);
	}
#endif

	blink(BLINK_FREQ);
}


void blinkCommand(__attribute__((unused)) int argc, __attribute__((unused)) char * argv[])
{
	blink(BLINK_FREQ);
}


void ledCommand(int argc, char * argv[])
{
	if ((argc > 1) && (strcmp(argv[1], "on")))
	{
		printStr("LED: on\n");
		gpioValSet(47, GPIO_VAL_ON);
	}
	else if ((argc > 1) && (strcmp(argv[1], "off")))
	{
		printStr("LED: off\n");
		gpioValSet(47, GPIO_VAL_OFF);
	}
	else
	{
		printStr("usage: ");
		printStr(argv[0]);
		printStr(" <on|off>\n");
	}
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


