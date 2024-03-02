#include <stdint.h>
#include "rpi_arch.h"
#include "utils.h"



void blink(void);



/**
*	C entry point
*/
void entryC(void)
{
	printStr("\r\nHello World!\r\n\r\n");

	blink();
}


void blink(void)
{
	uint32_t regVal32;
	uint32_t i = 0;
	uint64_t prevSysTime = 0;
	uint64_t currSysTime = 0;

	regVal32 = regRead32(GPFSEL4);
	regVal32 &= ~(7 << 21);
	regVal32 |= 1 << 21;
	regWrite32(GPFSEL4, regVal32);

	while (1)
	{
		/* Set bit */
		regWrite32(GPSET1, 1 << (47 - 32));

		/* delay */
		sysTimerDelay(1000000);

    	/* Clear bit */
    	regWrite32(GPCLR1, 1 << (47 - 32));

		/* delay */
		sysTimerDelay(1000000);

		currSysTime = sysTimerGet();
		printStr("System timer = ");
		printVal64Hex(currSysTime);
		if (i > 0)
		{
			printStr("\t(delta ");
			printVal32Hex(currSysTime - prevSysTime);
			printStr(")");
		}
		printStr("\n");
		prevSysTime = currSysTime;

		i++;
	}
}


