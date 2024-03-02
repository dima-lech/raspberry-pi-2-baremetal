#include <stdint.h>
#include "rpi_arch.h"
#include "utils.h"


#define BLINK_FREQ		1000000		/* 1 sec (?) */


void blink(uint32_t freq);



/**
*	C entry point
*/
void entryC(void)
{
	printStr("\r\n============");
	printStr("\r\nHello World!");
	printStr("\r\n============\r\n\r\n");

	blink(BLINK_FREQ);
}


void blink(uint32_t freq)
{
	uint32_t regVal32;
	uint32_t i = 0;
	uint64_t prevSysTime = 0;
	uint64_t currSysTime = 0;

	regVal32 = regRead32(GPFSEL4);
	regVal32 &= ~(7 << 21);
	regVal32 |= 1 << 21;
	regWrite32(GPFSEL4, regVal32);

	printStr("Start blink @ freq ");
	printValHex(freq, 0, "0x", "\r\n\r\n");

	while (1)
	{
		/* Set bit */
		regWrite32(GPSET1, 1 << (47 - 32));

		/* delay */
		sysTimerDelay(freq);

    	/* Clear bit */
    	regWrite32(GPCLR1, 1 << (47 - 32));

		/* delay */
		sysTimerDelay(freq);

		currSysTime = sysTimerGet();
		printStr("System timer = ");
		printValHex(currSysTime, 16, "0x", "");
		if (i > 0)
		{
			printStr("\t(delta ");
			printValHex(currSysTime - prevSysTime, 8, "0x", "");
			printStr(")");
		}
		printStr("\r\n");
		prevSysTime = currSysTime;

		i++;
	}
}


