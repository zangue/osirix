/*
 * uart.c
 * 
 * This file is part of Embedded-OS
 *
 * Copyright (c) 2015, Armand Zangue <armand@zangue.com>
 */

#include "gpio.h"

/* UART base address - Broadcom BCM2835 */
#define UART_BASE 0x20201000

/* UART register map */
struct uart {
	unsigned int dr;	/* Data register */
	unsigned int rsrecr;
	unsigned int fr;	/* Flag register */
	unsigned int ilpr;	/* Not in use */
	unsigned int ibrd;	/* Integer baud rate divisor */
	unsigned int fbrd;	/* Fractional baud rate divisor */
	unsigned int lcrh;	/* Line control register */
	unsigned int cr;	/* Control register */
	unsigned int ifls;	/* Interupt FIFO level select register */
	unsigned int imsc;	/* Interupt mask set clear register */
	unsigned int ris;	/* Raw status interupt register */
	unsigned int mis;	/* Mask interupt status register */
	unsigned int icr; 	/* Interupt clear register */
	unsigned int dmacr; 	/* DMA control register */
	unsigned int itcr; 	/* Test control register */
	unsigned int itip;	/* Integration test register */
	unsigned int itop;	/* Integration test output register */
	unsigned int tdr;	/* Test data reg */
};

/* UART object */
static volatile struct uart * const uart = (struct uart *)UART_BASE;

#define UART_RX        (1 << 4)
#define UART_TX        (1 << 5)

/* Settings */
#define UART_CLOCK	3000000	/* 3MHz */
#define UART_BAUD	115200

void uart_init(void)
{
	/* Disable uart */
	uart->cr = 0x00000000;

	/* Set up I/O pins */
	gpio_uart_init();

	/* Disable interupts */
	uart->icr = 0x7ff;
	
	/*
	 * Set baud rate: for this purpose we need to set the integer and
	 * fractional part of the baud rate divisor.
	 *
	 * From Broadcom BCM2835 Manual, page 183:
	 * The baud rate divisor is calculated as follows:
	 * BAUDDIV = (FUARTCLK / (16 Baud rate))
	 * where FUARTCLK is the UART reference clock frequency. The BAUDDIV is
	 * comprised of the integer value IBRD and the fractional value FBRD. 
	 * 
	 * NOTE:
	 * The contents of the IBRD and FBRD registers are not up
	 * dated until transmission or reception of the current character is
	 * complete.
	 *
	 * If the required baud rate is 115200 and UART_CLOCK = 3MHz then:
	 * Baud Rate Divisor = 3000000 / (16 × 115200) = 1.627
	 * This means IBRD = 1 and FBRD = 0.627.
	 * Therefore, fractional part, m = integer ( (0.627 × 64) + 0.5 ) = 40
	 * Generated baud rate divider = 1 + 45/64 = 1.703
	 * Generated baud rate = 3000000 / (16 × 1.703) = 110099
	 * Error = (115200 - 110099) / 110099 × 100 = 4.633%
	 */
	uart->ibrd = 1;
	uart->fbrd = 40;

	/* Set UART for 8 bits, one stop, no parity */
	uart->lcrh = (1 << 4) | (1 << 5) | (1 << 6);

	/* Mask all interupts */
	uart->imsc = (1 << 1) | (1 << 4) | (1 << 5) | (1 << 6) |
	                      (1 << 7) | (1 << 8) | (1 << 9) | (1 << 10);

	/* Enable UART */
	uart->cr = (1 << 0) | (1 << 8) | (1 << 9);                     
}

char uart_rx(void)
{
	while(uart->fr & UART_RX) {}
	return uart->dr;
}

void uart_tx(char byte)
{
	while(uart->fr & UART_TX) {}
	uart->dr = byte;
}


