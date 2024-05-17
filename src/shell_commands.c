#include <stdint.h>
#include "dlsh.h"
#include "rpi_arch.h"
#include "utils.h"


void blink(void);

static void shBlink(__attribute__((unused)) int argc, __attribute__((unused)) char * argv[]);
static void shLed(int argc, char * argv[]);
static void shRead32(int argc, char * argv[]);
static void shDump(int argc, char * argv[]);



void shRegisterCommands(void)
{
	dlshRegisterCommand("blink", 	shBlink);
	dlshRegisterCommand("led", 		shLed);
	dlshRegisterCommand("mr",		shRead32);
	dlshRegisterCommand("d",		shDump);
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
		printStr("Read 32-bit memory address.\r\n");
		printStr("usage: ");
		printStr(argv[0]);
		printStr(" <hex address>\r\n");
	}
	else
	{
		if (!strIsHex(argv[1]))
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



static void shDump(int argc, char * argv[])
{
	static int addressIsSet = 0;
	static uint32_t address = 0x0;
	static uint32_t length = 0x4;
	int printUsage = 0;
	uint32_t value = 0x0;
	uint32_t i;
	uint32_t j;
	uint32_t k;
	char charBuffer[17];
	uint32_t charBufferIndex = 0;


	if (argc <= 1)
	{
		if (0 == addressIsSet)
		{
			printUsage = 1;
		}
	}
	if (argc >= 2)
	{
		if (!strIsHex(argv[1]))
		{
			printUsage = 1;
		}
		else
		{
			address = strToHex32(&argv[1][2]);
			address = address & 0xfffffffc;
			addressIsSet = 1;
		}
	}
	if (argc >= 3)
	{
		if (strIsHex(argv[2]))
		{
			length = strToHex32(argv[2]);
		}
		else
		{
			length = strToDec32(argv[2]);	
		}
	}

	if (printUsage)
	{
		printStr("Dump memory content.\r\n");
		printStr("usage: ");
		printStr(argv[0]);
		printStr(" [hex address] [length]\r\n");
		
		if (0 == addressIsSet)
		{
			printStr("Address not set!\r\n");
		}

		return;
	}


	/* Print memory dump */
	for (i = 0; i < length; i++)
	{
		if ((0 == i) || ((address % 0x10) == 0))
		{
			if (i > 0)
			{
				charBuffer[charBufferIndex] = CHAR_NULL;
				charBufferIndex = 0;
				printStr("\t/");
				printStr(charBuffer);
				printStr("/\r\n");
			}
			printValHex(address & 0xfffffff0, 8, "", " :");
		}

		/* Print first blanks */
		if (0 == i)
		{
			for (j = 0; j < ((address % 0x10) / 0x4); j++)
			{
				printStr("         ");

				for (k = 0; k < 4; k++)
				{
					charBuffer[charBufferIndex++] = ' ';
				}
			}
		}

		value = regRead32(address);
		printValHex(value, 8, " ", "");
		for (k = 0; k < 4; k++)
		{
			j = value & 0xff;
			value >>= 8;

			if ((j >= 32) && (j <= 127))
			{
				charBuffer[charBufferIndex++] = (char)j;
			}
			else
			{
				charBuffer[charBufferIndex++] = '.';
			}
		}

		address += 0x4;
	}

	/* Print last blanks */
	for (i = address; (i % 0x10) != 0x0; i += 4)
	{
		printStr("         ");

		for (k = 0; k < 4; k++)
		{
			charBuffer[charBufferIndex++] = ' ';
		}
	}

	charBuffer[charBufferIndex] = CHAR_NULL;
	printStr("\t/");
	printStr(charBuffer);
	printStr("/\r\n");

}

