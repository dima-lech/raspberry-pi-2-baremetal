#include <stdint.h>
#include "rpi_arch.h"


void delay(uint32_t val)
{
	while (val > 0)
	{
		val--;
	}
}
