/*
 * vsprintf.c
 *
 * This file is part of Embedded-OS
 *
 * Copyright (c) 2015, Armand Zangue <armand@zangue.com>
 */

#include <stdarg.h>
#include "uart.h"

static void print_hex(unsigned int val, int do_prefix, int width)
{
	char hex_mask[] = "0123456789abcdef";
	unsigned int nibble;
	int i;

	if (do_prefix) {
		uart_tx('0');
		uart_tx('x');
	}

	for (i = 7; i >= 0; i--) {
		nibble = (val >> (4 * i)) & 0xf;

		/* skip the zeros at the begining */
		if (!nibble && i >= width)
			continue;

		uart_tx(hex_mask[nibble]);

		/* After starting output don't ignore zero anymore */
		width = 8;
	}
}

static void print_string(char *s)
{
	while(*s)
		uart_tx(*s++);
}

static void print_dec(int d)
{
	if (d & (1 << 31)) {
		d = ~d; d++;
		uart_tx('-');
	}

	if (d >= 10)
		print_dec(d / 10);

	uart_tx(d % 10 + '0');
}

__attribute__ ((format(printf,1,2)))
void vsprintf(char *fmt, ...)
{
	va_list ap;
	
	va_start(ap, fmt);

	while (*fmt) {
		/* Normal char? */
		if (*fmt != '%') {
			uart_tx(*fmt++);
			continue;
		}

		/* found format */
		fmt++;

		/* format unexpectedly ends? */
		if (!*fmt) {
			uart_tx('%');
			break;
		}

		switch (*fmt) {
		case 'c':
			uart_tx(va_arg(ap, unsigned int));
			break;
		case 's':
			print_string(va_arg(ap, char*));
			break;
		case 'p':
			print_hex(va_arg(ap, unsigned int), 1, 8);
			break;
		case 'x':
			print_hex(va_arg(ap, unsigned int), 1, 1);
		case 'i':
		case 'd':
			print_dec(va_arg(ap, int));
			break;
		case '%':
			uart_tx('%');
			break;
		default:
			uart_tx('%');
			uart_tx(*fmt);
		}
		fmt++;
	}
	va_end(ap);
}

