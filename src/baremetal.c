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

	/**
	 * Set GPIO 47 as output:
	 * GPFSEL4[FSEL47][23:21] = 001
	 */
	regVal32 = regRead32(GPFSEL4);
	regVal32 &= ~(7 << 21);
	regVal32 |= 1 << 21;
	regWrite32(GPFSEL4, regVal32);

	printStr("Start blink @ ");
	printValDec(freq, "", " Hz\r\n\r\n");

	while (1)
	{
		/* Set GPIO 47: GPSET1[SET47][47-32] = 1 */
		regWrite32(GPSET1, 1 << (47 - 32));

		/* delay */
		sysTimerDelay(freq);

    	/* Clear GPIO 47: GPCLR1[CLR47][47-32] = 1 */
    	regWrite32(GPCLR1, 1 << (47 - 32));

		/* delay */
		sysTimerDelay(freq);

		currSysTime = sysTimerGet();
		printStr("System timer = ");
		printValHex(currSysTime, 16, "0x", "");
		if (i > 0)
		{
			printStr("\t(delta ");
			printValDec((uint32_t)(currSysTime - prevSysTime), "", "");
			printStr(")");
		}
		printStr("\r\n");
		prevSysTime = currSysTime;

		i++;
	}
}


