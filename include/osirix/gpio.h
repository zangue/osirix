#ifndef _GPIO_H
#define _GPIO_H

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
	const unsigned int reserved1;
	unsigned int gpset0;	/* GPIO Pin Output Set 0 */
	unsigned int gpset1;	/* GPIO Pin Output Set 1 */
	const unsigned int reserved2;
	unsigned int gpclr0;	/* GPIO Pin Output Clear 0 */
	unsigned int gpclr1;	/* GPIO Pin Output Clear 1 */
	const unsigned int reserved3;
	unsigned int gplev0;	/* GPIO Pin Level 0 */
	unsigned int gplev1;	/* GPIO Pin Level 1 */
	const unsigned int reserved4;
	unsigned int gpeds0;	/* GPIO Pin Event Detect Status 0 */
	unsigned int gpeds1;	/* GPIO Pin Event Detect Status 1 */
	const unsigned int reserved5;
	unsigned int gpren0;	/* GPIO Pin Rising Edge Detect Enable 0 */
	unsigned int gpren1;	/* GPIO Pin Rising Edge Detect Enable 1 */
	const unsigned int reserved6;
	unsigned int gpfen0;	/* GPIO Pin Falling Edge Detect Enable 0 */
	unsigned int gpfen1;	/* GPIO Pin Falling Edge Detect Enable 1 */
	const unsigned int reserved7;
	unsigned int gphen0;	/* GPIO Pin High Detect Enable 0 */
	unsigned int gphen1;	/* GPIO Pin High Detect Enable 1 */
	const unsigned int reserved8;
	unsigned int gplen0;	/* GPIO Pin Low Detect Enable 0 */
	unsigned int gplen1;	/* GPIO Pin Low Detect Enable 1*/
	const unsigned int reserved9;
	unsigned int gparen0;	/* GPIO Pin Async. Rising Edge Detect 0 */
	unsigned int gparen1;	/* GPIO Pin Async. Rising Edge Detect 1 */
	const unsigned int reserved10;
	unsigned int gpafen0; 	/* GPIO Pin Async. Falling Edge Detect 0 */
	unsigned int gpafen1;	/* GPIO Pin Async. Falling Edge Detect 1 */
	const unsigned int reserved11;
	unsigned int gppud;	/* GPIO Pin Pull-up/down Enable */
	unsigned int gppudclk0;	/* GPIO Pin Pull-up/down Enable Clock 0 */
	unsigned int gppudclk1;	/* PIO Pin Pull-up/down Enable Clock 1 */
	const unsigned int reserved12;
	unsigned int test;
};

volatile struct gpio * const gpio = (struct gpio *) GPIO_BASE;

void gpio_ok_led_blink(void);
void gpio_uart_init(void);

/*
 * The 54 general purpose I/O (GPIO) of the RPI.
 */
typedef enum {
	GPIO0 = 0,
  GPIO1, GPIO2, GPIO3, GPIO4, GPIO5, GPIO6, GPIO7, GPIO8, GPIO9,
  GPIO10 = 10,
  GPIO11, GPIO12, GPIO13, GPIO14, GPIO15, GPIO16, GPIO17, GPIO18, GPIO19,
  GPIO20 = 20,
  GPIO21, GPIO22, GPIO23, GPIO24, GPIO25, GPIO26, GPIO27, GPIO28, GPIO29,
  GPIO30 = 30,
  GPIO31, GPIO32, GPIO33, GPIO34, GPIO35, GPIO36, GPIO37, GPIO38, GPIO39,
  GPIO40 = 40,
  GPIO41, GPIO42, GPIO43, GPIO44, GPIO45, GPIO46, GPIO47, GPIO48, GPIO49,
  GPIO50 = 50,
  GPIO51, GPIO52, GPIO53,
} gpio_pin_t;

typedef enum {
	INPUT = 0, // 000
	OUTPUT, // 001
} gpio_pin_mode_t;

/*
 * All  GPIO  pins  have  at least two (up to five) alternative functions within BCM.
 */
typedef enum {
	ALT5 = 2, // 010
	ALT4, // 011
	ALT0, // 100
	ALT1, // 101
	ALT2, // 110
	ALT3, // 111
} gpio_pin_fn_t;

typedef enum {
	LOW = 0,
	HIGH,
	UNKNOW,
} gpio_pin_value_t;

/* Arduino-like library for GPIO */
void gpio_pin_function(gpio_pin_t pin, gpio_pin_fn_t func);
void gpio_pin_mode(gpio_pin_t pin, gpio_pin_mode_t mode);
void gpio_pin_write(gpio_pin_t pin, gpio_pin_value_t value);
gpio_pin_value_t gpio_pin_read(gpio_pin_t pin);

#endif /* _GPIO_H */
