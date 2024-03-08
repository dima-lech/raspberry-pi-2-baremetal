#include <stdint.h>
#include "rpi_arch.h"
#include "utils.h"



#undef DEBUG_FLAG

#ifdef	DEBUG_FLAG
	#define DEBUG_PRINT(x)		x
#else
	#define DEBUG_PRINT(x)
#endif


void sysTimerDelay(uint32_t delayVal)
{
	uint64_t startVal;
	uint64_t currVal;

	startVal = sysTimerGet();

	/* Wait for specified duration */
	do
	{
		currVal = sysTimerGet();
	} while ((currVal - startVal) < ((uint64_t)delayVal));
}


void uartPutC(char c)
{
	/* Wait until UART ready */
	while (regRead32(UART0_FR) & (1 << 5));
	/* Write character */
	regWrite32(UART0_DR, c);
}


uint64_t sysTimerGet(void)
{
	uint32_t lo;
	uint32_t hi;
	uint32_t flagOk = 0;
	uint64_t result;

	do
	{
		hi = regRead32(SYS_TIMER_CHI);
		lo = regRead32(SYS_TIMER_CLO);

		if (regRead32(SYS_TIMER_CHI) == hi)
		{
			flagOk = 1;
		}
	} while (0 == flagOk);

	result = ((uint64_t)hi << 32) | lo;

	return result;
}


void gpioFselSet(uint32_t gpio, GPIO_FSEL_TYPE fsel)
{
	uint32_t gpfselReg;
	uint32_t gpfselBit;
	uint32_t gpfselVal;

	if (gpio >= GPIO_NUM)
	{
		printValDec(gpio, "Invalid GPIO: ", "\r\n");
		return;
	}

	gpfselReg = GPFSEL0 + ((gpio / GPIO_FSEL_FIELD_NUM) * sizeof(uint32_t));
	gpfselBit = (gpio % GPIO_FSEL_FIELD_NUM) * GPIO_FSEL_FIELD_SIZE;

	DEBUG_PRINT(printValHex(gpfselReg, 8, "DBG: gpfselReg = 0x", "\r\n"));
	DEBUG_PRINT(printValHex(gpfselBit, 8, "DBG: gpfselBit = 0x", "\r\n"));

	/* Clear FSELn */
	gpfselVal = regRead32(gpfselReg);
	DEBUG_PRINT(printValHex(gpfselVal, 8, "DBG: gpfselVal = 0x", "\r\n"));
	gpfselVal = gpfselVal & ~(GPIO_FSEL_FIELD_MASK << gpfselBit);
	/* Write FSELn field value */
	gpfselVal = gpfselVal | (fsel << gpfselBit);
	regWrite32(gpfselReg, gpfselVal);
	DEBUG_PRINT(printValHex(gpfselVal, 8, "DBG: gpfselVal = 0x", "\r\n"));
}


void gpioValSet(uint32_t gpio, GPIO_VAL_TYPE val)
{
	uint32_t gpioReg;
	uint32_t regVal;

	if (gpio >= GPIO_NUM)
	{
		printValDec(gpio, "Invalid GPIO: ", "\r\n");
		return;
	}

	if (GPIO_VAL_OFF == val)
	{
		gpioReg = GPCLR0;
	}
	else if (GPIO_VAL_ON == val)
	{
		gpioReg = GPSET0;
	}
	else
	{
		return;
	}

	gpioReg = gpioReg + ((gpio / GPIO_CLR_SET_FIELD_NUM) * sizeof(uint32_t));
	DEBUG_PRINT(printValHex(gpioReg, 8, "DBG: gpioReg = 0x", "\r\n"));
	regVal = 0x1 << (gpio % GPIO_CLR_SET_FIELD_NUM);
	DEBUG_PRINT(printValHex(regVal, 8, "DBG: regVal = 0x", "\r\n"));

	/* Set bit */
	regWrite32(gpioReg, regVal);
}

