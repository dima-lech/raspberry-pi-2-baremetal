#include <stdint.h>
#include "rpi_arch.h"
#include "utils.h"


#define STR_BUFF_SIZE	18

static char strBuff[STR_BUFF_SIZE];


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


char hexToChar(uint8_t val8)
{
	if (val8 <= 9)
	{
		return ('0' + val8);
	}
	else
	{
		return('A' + (val8 - 0xa));
	}
}


void printValHex(uint64_t val, uint32_t padNum, char * prefix, char * suffix)
{
	int32_t i;
	uint32_t printChars = 0;

	strBuff[STR_BUFF_SIZE - 1] = '\0';

	for(i = STR_BUFF_SIZE - 2; (i >= 0) && (val > 0); i--)
	{
		if (8 == printChars)
		{
			strBuff[i--] = '_';
			printChars++;
		}

		strBuff[i] = hexToChar((uint8_t)(val & 0xf));
		val = val >> 4;
		printChars++;
	}

	while ((printChars < padNum) && (i >= 0))
	{
		if (8 == printChars)
		{
			strBuff[i--] = '_';
			printChars++;
		}

		strBuff[i] = '0';
		printChars++;
		i--;
	}

	printStr(prefix);
	printStr(&strBuff[i + 1]);
	printStr(suffix);
}


void printValDec(uint32_t val, char * prefix, char * suffix)
{
	int32_t i;
	uint32_t printChars = 0;

	strBuff[STR_BUFF_SIZE - 1] = '\0';

	for(i = STR_BUFF_SIZE - 2; (i >= 0) && (val > 0); i--)
	{
		if ((printChars > 0) && ((printChars % 3) == 0))
		{
			strBuff[i--] = ',';
		}

		strBuff[i] = hexToChar((uint8_t)(val % 10));
		val = val / 10;
		printChars++;
	}

	printStr(prefix);
	printStr(&strBuff[i + 1]);
	printStr(suffix);
}
