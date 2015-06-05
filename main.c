/*
 * main.c
 *
 * This file is part of Embedded-OS
 *
 * Copyright (c) 2015, Armand Zangue <armand@zangue.com>
 */

#include "uart.h"
#include "gpio.h"
#include "printk.h"


static void __annouce(void);

void start_kernel(unsigned int r0, unsigned int r1, unsigned atags)
{
	char c;

	(void) r0;
	(void) r1;
	(void) atags;

	uart_init();

// 	gpio_ok_led_blink(); 
	
	__annouce();
	
	printk("Hello, World!\n");
	printk("At the moment I can just print format string and echo character I get.\n");
	printk("Let me show you a demo\n");

	printk("A character: %c\n", '@');
	printk("A string: %s\n", "My name is Embedded-OS.");
	printk("A number: %x", 0x12345678);
	
	while (1) {
 		c = uart_rx(); 
 		printk("You pressed '%c', it's representation in Hex is: %x\r\n", c, c);
 	}
}

static void __annouce(void)
{
	printk("\033[1m"); // Bold text
 	printk("\n\r");
	printk("\n\r\t\tWelcome to Embedded-OS - A bare metal kernel \n\r");
	printk("\n\r");
	printk("\033[0m"); // Bold text ends
}
