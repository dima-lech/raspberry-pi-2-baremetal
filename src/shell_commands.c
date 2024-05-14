#include <stdint.h>
#include "dlsh.h"
#include "rpi_arch.h"
#include "utils.h"


void blink(void);

static void shBlink(__attribute__((unused)) int argc, __attribute__((unused)) char * argv[]);
static void shLed(int argc, char * argv[]);



void shRegisterCommands(void)
{
	dlshRegisterCommand("blink", 	shBlink);
	dlshRegisterCommand("led", 		shLed);
}




static void shBlink(__attribute__((unused)) int argc, __attribute__((unused)) char * argv[])
{
	dlshExit();
	blink();
}

static void shLed(int argc, char * argv[])
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


