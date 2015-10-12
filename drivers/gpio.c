/*
 * drivers/gpio.c
 *
 * Copyrigth (c) 2015, Armand Zangue <armand@zangue.com>
 */

#include <osirix/gpio.h>

void gpio_pin_function(gpio_pin_t pin, gpio_pin_fn_t func)
{
	volatile unsigned int * gpfselx_ptr;
	unsigned int reg_value;
	unsigned int clear_mask = 0x7;
	unsigned int fn_shift = (pin % 10 ) * 3; /* shift amount to reach fn bit of particular pin */

	/*
	 * They are 5 'function select' registers for all the 54 GPIO pins.
	 * Each register cover range of GPIO pins as follow:
	 *  GPFSEL0 => [pin 0, pin 9] - offset 0
	 *  GPFSEL1 => [pin 10, pin 19] - offset 1
	 *  GPFSEL2 => [pin 20, pin 29] - offset 2
	 *  ...
	 *  GPFSEL5 => [pin 50, pin 54] - offset 5
	 *
	 * We can access this register with the rigth offset like this:
	 * gpfselx = gpio[offset] e.g for pin 35 it would be gpfsel3 = gpio[3]
	 * so we get the rigth offset for particular by dividing pin number by 10
	 */
	gpfselx_ptr = &((unsigned int * ) gpio)[ pin / 10 ];
	reg_value = *gpfselx_ptr;

	/* First clear function select bits for this pin */
	reg_value &= ~(clear_mask << fn_shift);

	/* Set desired function */
	reg_value |= (func << fn_shift);

	*gpfselx_ptr = reg_value;
}

void gpio_pin_mode(gpio_pin_t pin, gpio_pin_mode_t mode)
{
	gpio_pin_function(pin, (gpio_pin_fn_t) mode);
}

void gpio_pin_write(gpio_pin_t pin, gpio_pin_value_t value)
{
	switch(value) {
		case HIGH:
			/*
			 * Two registers are provided to set all the 54 GPIO pins: gpset0 and gpset1
			 * the nth bit of gpset0 configure the nth pin while the nth bit of gpset1 configure the
			 * (n+32)th pin.
			 */
			if (pin >= 0 && pin < 32) {
				gpio->gpset0 = (1 << pin);
				break;
			} else if (pin >= 32 && pin < 55) {
				gpio->gpset1 = (1 << (pin - 32));
				break;
			}
			else
				break;

		case LOW:
			if (pin >= 0 && pin < 32) {
				gpio->gpclr0 = (1 << pin);
				break;
			} else if (pin >= 32 && pin < 55) {
				gpio->gpclr1 = (1 << (pin - 32));
				break;
			}
			else
				break;

		default:
			break;
	}

	return;
}

gpio_pin_value_t gpio_pin_read(gpio_pin_t pin)
{
	gpio_pin_value_t value = UNKNOW;

	if (pin >= 0 && pin < 32)
		value = gpio->gplev0 & (1 << pin);
	else if (pin >= 32 && pin < 55)
		value = gpio->gplev1 & (1 << (pin - 32));
	else
		return value;

	if (value)
		value = HIGH;
	else
		value = LOW;

	return value;
}

#if 0
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
#endif
