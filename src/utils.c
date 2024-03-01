#include <stdint.h>
#include "rpi_arch.h"
#include "utils.h"

void printStr(const char * str)
{
	if (0 == str)
	{
		return;
	}

	while (*str != '\0')
	{
		uartPutC(*str);
		str++;
	}
}


void printVal32Hex(uint32_t val)
{
	uint32_t i;
	char c;

	uartPutC('0');
	uartPutC('x');
	for (i = 0; i < 8; i++)
	{
		c = (val & 0xf0000000) >> 28;
		if (c <= 9)
		{
			uartPutC('0' + c);
		}
		else
		{
			uartPutC('A' + (c - 0xa));
		}
		val = val << 4;
	}
}


void printVal64Hex(uint64_t val)
{
	uint32_t i;
	char c;

	uartPutC('0');
	uartPutC('x');
	for (i = 0; i < 16; i++)
	{
		c = (val & 0xf000000000000000llu) >> 60;
		if (c <= 9)
		{
			uartPutC('0' + c);
		}
		else
		{
			uartPutC('A' + (c - 0xa));
		}
		val = val << 4;

		if (i == 7)
		{
			uartPutC('_');
		}
	}
}


