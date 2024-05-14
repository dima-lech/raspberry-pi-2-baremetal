#include <stdint.h>
#include "dlsh.h"
#include "rpi_arch.h"
#include "utils.h"


void blink(void);

static void shBlink(__attribute__((unused)) int argc, __attribute__((unused)) char * argv[]);
static void shLed(int argc, char * argv[]);
static void shRead32(int argc, char * argv[]);



void shRegisterCommands(void)
{
	dlshRegisterCommand("blink", 	shBlink);
	dlshRegisterCommand("led", 		shLed);
	dlshRegisterCommand("read32",	shRead32);
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


static void shRead32(int argc, char * argv[])
{
	uint32_t address = 0x0;
	uint32_t value = 0x0;
	
	if (argc <= 1)
	{
		printStr("usage: ");
		printStr(argv[0]);
		printStr(" <hex address>\r\n");
	}
	else
	{
		if ((argv[1][0] != '0') || (argv[1][1] != 'x') ||
			(argv[1][2] == CHAR_NULL))
		{
			printStr("expected hex address!\r\n");
			return;
		}

		address = strToHex32(&argv[1][2]);
		printValHex(address, 8, "0x", " :\t");

		value = regRead32(address);
		printValHex(value, 8, "", "\r\n");
	}

}


