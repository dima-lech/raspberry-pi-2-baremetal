#ifndef     __RPI_ARCH_H
#define     __RPI_ARCH_H

#include <stdint.h>


#define regRead32(addr)         (*(volatile uint32_t*)(addr))
#define regWrite32(addr, val)   (*(volatile uint32_t*)(addr) = (val))

enum
{
    /* The GPIO registers base address */
    /* Bus address: 0x7E200000 */
    GPIO_BASE = 0x3F200000, /* for raspi2 & 3, 0x20200000 for raspi1 */

    GPFSEL4     = (GPIO_BASE + 0x10),
    GPSET1      = (GPIO_BASE + 0x20),
    GPCLR1      = (GPIO_BASE + 0x2C),
    GPPUD       = (GPIO_BASE + 0x94),
    GPPUDCLK0   = (GPIO_BASE + 0x98),

    /* The base address for UART */
    /* Bus address: 0x7E201000 */
    UART0_BASE = 0x3F201000, /* for raspi2 & 3, 0x20201000 for raspi1 */

    UART0_DR     = (UART0_BASE + 0x00),
    UART0_RSRECR = (UART0_BASE + 0x04),
    UART0_FR     = (UART0_BASE + 0x18),
    UART0_ILPR   = (UART0_BASE + 0x20),
    UART0_IBRD   = (UART0_BASE + 0x24),
    UART0_FBRD   = (UART0_BASE + 0x28),
    UART0_LCRH   = (UART0_BASE + 0x2C),
    UART0_CR     = (UART0_BASE + 0x30),
    UART0_IFLS   = (UART0_BASE + 0x34),
    UART0_IMSC   = (UART0_BASE + 0x38),
    UART0_RIS    = (UART0_BASE + 0x3C),
    UART0_MIS    = (UART0_BASE + 0x40),
    UART0_ICR    = (UART0_BASE + 0x44),
    UART0_DMACR  = (UART0_BASE + 0x48),
    UART0_ITCR   = (UART0_BASE + 0x80),
    UART0_ITIP   = (UART0_BASE + 0x84),
    UART0_ITOP   = (UART0_BASE + 0x88),
    UART0_TDR    = (UART0_BASE + 0x8C),
};



void delay(uint32_t val);
void uart_putc(char c);


#endif    /* __RPI_ARCH_H */
