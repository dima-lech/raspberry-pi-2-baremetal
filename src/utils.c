#include <stdint.h>
#include "rpi_arch.h"
#include "utils.h"

void print_str(const char * str)
{
	if (0 == str)
	{
		return;
	}

	while (*str != '\0')
	{
		uart_putc(*str);
		str++;
	}
}


void print_val32_hex(uint32_t val)
{
	uint32_t i;
	char c;

	uart_putc('0');
	uart_putc('x');
	for (i = 0; i < 8; i++)
	{
		c = (val & 0xf0000000) >> 28;
		if (c <= 9)
		{
			uart_putc('0' + c);
		}
		else
		{
			uart_putc('A' + (c - 0xa));
		}
		val = val << 4;
	}
}


