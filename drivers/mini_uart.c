/*
 * drivers/mini_uart.c
 *
 * Copyright (c) 2015, Armand Zangue
 */

#include <osirix/kernel.h>
#include <osirix/device.h>
#include <osirix/aux.h>
#include <osirix/gpio.h>
#include <osirix/init.h>

/* default baud value */
#define BAUD	115200

#define MU_LCR_8BIT_MODE (1 << 1)

/* AUX Object */
static volatile struct aux * const aux = (struct aux *) AUX_BASE;

char mini_uart_rx(void)
{
	return 'a';
}

void mini_uart_tx(const char byte)
{

}

//static int __init mini_uart_init(void)
void mini_uart_init(void)
{
	volatile unsigned int i;

	/* GPIO pins should be setup first before enabling the UART */
	//TODO

	/* Mini UART needs to be enabled before it can be used */
	aux->enables = MU_ENABLE;

	/* Disable interrupts */
	aux->irq &= ~MU_IRQ;

	aux->ier = 0;

	/* We do not need extra features */
	aux->mu_cntl_reg = 0;

	/* Make it operate in 8 bit mode */
	aux->mu_lcr_reg = MU_LCR_8BIT_MODE;

	aux->mu_mcr_reg = 0;

	aux->mu_ier_reg = 0;

	aux->mu_iir_reg = 0xc6;

	aux->mu_baud_reg = (SYS_HZ / (8 * BAUD)) - 1;

	return;
}

//static void __exit mini_uart_exit(void)
static void mini_uart_exit(void)
{

}

//device_init(mini_uart_init);
//device_exit(mini_uart_exit);
