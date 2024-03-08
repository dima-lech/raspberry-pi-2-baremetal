#ifndef     __RPI_ARCH_H
#define     __RPI_ARCH_H

#include <stdint.h>

/**
 * Peripherals addresses in documentation are referred to using
 * "bus" addresses, which are used by the GPU side (VPU/VC4).
 * Thus peripheral addresses have to be translated to Arm physical
 * region, which starts at 0x20200000 for RPi 1 and 0x3F000000
 * for RPi 2 & 3.
 **/
#define PERIPH_BUS_BASE_ADDR    0x7E000000
#define PERIPH_ARM_BASE_ADDR    0x3F000000      /* For RPi 2 & 3 */
#define PERIPH_BUS_TO_ARM_ADDR(addr)    \
   ((addr) - (PERIPH_BUS_BASE_ADDR) +   \
                (PERIPH_ARM_BASE_ADDR))


#define regRead32(addr)         (*(volatile uint32_t*)(addr))
#define regWrite32(addr, val)   (*(volatile uint32_t*)(addr) = (val))

enum
{
    /* System Timer     0x7E003000  */
    SYS_TIMER_BASE  = PERIPH_BUS_TO_ARM_ADDR(0x7E003000),
    SYS_TIMER_CLO   = (SYS_TIMER_BASE + 0x04),      /* System Timer Counter Lower 32 bits */
    SYS_TIMER_CHI   = (SYS_TIMER_BASE + 0x08),      /* System Timer Counter Higher 32 bits */

    /* GPIO             0x7E200000  */
    GPIO_BASE       = PERIPH_BUS_TO_ARM_ADDR(0x7E200000),
    GPFSEL0         = (GPIO_BASE + 0x00),
    GPFSEL1         = (GPIO_BASE + 0x04),
    GPFSEL2         = (GPIO_BASE + 0x08),
    GPFSEL3         = (GPIO_BASE + 0x0C),
    GPFSEL4         = (GPIO_BASE + 0x10),
    GPFSEL5         = (GPIO_BASE + 0x14),
    GPSET0          = (GPIO_BASE + 0x1C),
    GPSET1          = (GPIO_BASE + 0x20),
    GPCLR0          = (GPIO_BASE + 0x28),
    GPCLR1          = (GPIO_BASE + 0x2C),
    GPPUD           = (GPIO_BASE + 0x94),
    GPPUDCLK0       = (GPIO_BASE + 0x98),

    /* UART0            0x7E201000  */
    UART0_BASE      = PERIPH_BUS_TO_ARM_ADDR(0x7E201000),
    UART0_DR        = (UART0_BASE + 0x00),
    UART0_RSRECR    = (UART0_BASE + 0x04),
    UART0_FR        = (UART0_BASE + 0x18),
    UART0_ILPR      = (UART0_BASE + 0x20),
    UART0_IBRD      = (UART0_BASE + 0x24),
    UART0_FBRD      = (UART0_BASE + 0x28),
    UART0_LCRH      = (UART0_BASE + 0x2C),
    UART0_CR        = (UART0_BASE + 0x30),
    UART0_IFLS      = (UART0_BASE + 0x34),
    UART0_IMSC      = (UART0_BASE + 0x38),
    UART0_RIS       = (UART0_BASE + 0x3C),
    UART0_MIS       = (UART0_BASE + 0x40),
    UART0_ICR       = (UART0_BASE + 0x44),
    UART0_DMACR     = (UART0_BASE + 0x48),
    UART0_ITCR      = (UART0_BASE + 0x80),
    UART0_ITIP      = (UART0_BASE + 0x84),
    UART0_ITOP      = (UART0_BASE + 0x88),
    UART0_TDR       = (UART0_BASE + 0x8C),
};



void delay(uint32_t val);
void uartPutC(char c);
void sys(char c);
uint64_t sysTimerGet(void);
void sysTimerDelay(uint32_t delayVal);


#endif    /* __RPI_ARCH_H */
