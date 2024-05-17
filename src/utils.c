#include <stdint.h>
#include "rpi_arch.h"
#include "utils.h"


#define STR_BUFF_SIZE	18


static char strBuff[STR_BUFF_SIZE];


static char charToHex(char c);



void printStr(const char * str)
{
	if (0 == str)
	{
		return;
	}

	while (*str != CHAR_NULL)
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

	strBuff[STR_BUFF_SIZE - 1] = CHAR_NULL;

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

	strBuff[STR_BUFF_SIZE - 1] = CHAR_NULL;

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


int strcmp(const char * str1, const char * str2)
{
	int i;

	for (i = 0; i < STR_BUFF_SIZE; i++)
	{
		if (str1[i] != str2[i])
		{
			return 0;
		}
		else if (str1[i] == CHAR_NULL)
		{
			return 1;
		}
	}

	return 0;
}


uint32_t strToHex32(char * str)
{
	uint32_t val = 0x0;
	uint32_t i = 0;

	if (0 == str)
	{
		return val;
	}

	for (i = 0; i < 8; i++)
	{
		if (str[i] == CHAR_NULL)
		{
			return val;
		}

		val <<= 4;
		val |= charToHex(str[i]);
	}

	return val;
}


uint32_t strToDec32(char * str)
{
	uint32_t val = 0;
	uint32_t i = 0;

	if (0 == str)
	{
		return val;
	}

	for (i = 0; i < 8; i++)
	{
		if (str[i] == CHAR_NULL)
		{
			return val;
		}

		val *= 10;
		val += charToHex(str[i]);
	}

	return val;
}


static char charToHex(char c)
{
	if ((c >= 'a') && (c <= 'f'))
	{
		return (c - 'a' + 10);
	}
	else if ((c >= 'A') && (c <= 'F'))
	{
		return (c - 'A' + 10);
	}
	else if ((c >= '0') && (c <= '9'))
	{
		return (c - '0');
	}

	return 0;
}


int strIsHex(char * str)
{
	if (0 == str)
	{
		return 0;
	}

	if ((str[0] != '0') || (str[1] != 'x') ||
		(str[2] == CHAR_NULL))
	{
		return 0;
	}

	return 1;
}

