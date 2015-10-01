/*
 * drivers/gpio.c
 *
 * Copyrigth (c) 2015, Armand Zangue <armand@zangue.com>
 */

#include <stddef.h>
#include <stdint.h>

/* GPIO base address - Broadcom BCM2835 */
#define GPIO_BASE 0x20200000;

struct gpio {
	unsigned int gpfsel0;   /* GPIO Function select 0 */
	unsigned int gpfsel1;	/* GPIO Function select 1 */
	unsigned int gpfsel2;	/* GPIO Function select 2 */
	unsigned int gpfsel3;	/* GPIO Function select 3 */
	unsigned int gpfsel4;	/* GPIO Function select 4 */
	unsigned int gpfsel5;	/* GPIO Function select 5 */
	unsigned int reserved1;
	unsigned int gpset0;	/* GPIO Pin Output Set 0 */
	unsigned int gpset1;	/* GPIO Pin Output Set 1 */
	unsigned int reserved2;
	unsigned int gpclr0;	/* GPIO Pin Output Clear 0 */
	unsigned int gpclr1;	/* GPIO Pin Output Clear 1 */
	unsigned int reserved3;
	unsigned int gplev0;	/* GPIO Pin Level 0 */
	unsigned int gplev1;	/* GPIO Pin Level 1 */
	unsigned int reserved4;
	unsigned int gpeds0;	/* GPIO Pin Event Detect Status 0 */
	unsigned int gpeds1;	/* GPIO Pin Event Detect Status 1 */
	unsigned int reserved5;
	unsigned int gpren0;	/* GPIO Pin Rising Edge Detect Enable 0 */
	unsigned int gpren1;	/* GPIO Pin Rising Edge Detect Enable 1 */
	unsigned int reserved6;
	unsigned int gpfen0;	/* GPIO Pin Falling Edge Detect Enable 0 */
	unsigned int gpfen1;	/* GPIO Pin Falling Edge Detect Enable 1 */
	unsigned int reserved7;
	unsigned int gphen0;	/* GPIO Pin High Detect Enable 0 */
	unsigned int gphen1;	/* GPIO Pin High Detect Enable 1 */
	unsigned int reserved8;
	unsigned int gplen0;	/* GPIO Pin Low Detect Enable 0 */
	unsigned int gplen1;	/* GPIO Pin Low Detect Enable 1*/
	unsigned int reserved9;
	unsigned int gparen0;	/* GPIO Pin Async. Rising Edge Detect 0 */
	unsigned int gparen1;	/* GPIO Pin Async. Rising Edge Detect 1 */
	unsigned int reserved10;
	unsigned int gpafen0; 	/* GPIO Pin Async. Falling Edge Detect 0 */
	unsigned int gpafen1;	/* GPIO Pin Async. Falling Edge Detect 1 */
	unsigned int reserved11;
	unsigned int gppud;	/* GPIO Pin Pull-up/down Enable */
	unsigned int gppudclk0;	/* GPIO Pin Pull-up/down Enable Clock 0 */
	unsigned int gppudclk1;	/* PIO Pin Pull-up/down Enable Clock 1 */
	unsigned int reserved12;
	unsigned char test;
};

static volatile struct gpio * const gpio = (struct gpio *) GPIO_BASE;

#define LED_GPFBIT      18
#define LED_GPIO_BIT    16

static inline void delay(uint32_t count)
{
	asm volatile("__delay_%=: subs %[count], %[count], #1; bne __delay_%=\n"
			: : [count]"r" (count) : "cc");
}


void gpio_ok_led_blink(void)
{
	volatile unsigned int noops;
	/*
	 * The OK Led on the RPI Board is wired to GPIO pin 16 which is controlled
	 * by the bits 18 to 20 of the 'GPIO function select 1' (gpfsel1) register.
	 * Setting the control bits to '001' configure GPIO pin 16 as an output.
	 */
	gpio->gpfsel1 |= (1 << LED_GPFBIT);

	/* Clear GPIO pin 16 (Turn the OK LED on)*/
	gpio->gpclr0 |= (1 << LED_GPIO_BIT);

	/* Busy wait for some time */
	for (noops = 0; noops < 500000; noops++);

	/* Set GPIO pin 16 (Turn the OK LED off) */
	gpio->gpset1 |= (1 << LED_GPIO_BIT);
}

void gpio_uart_init(void)
{
	gpio->gppud = 0x00000000;

	delay(150);

	gpio->gppudclk0 = (1 << 14) | (1 << 15);

	delay(150);

	gpio->gppudclk0 = 0x00000000;
}
