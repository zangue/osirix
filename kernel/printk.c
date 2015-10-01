/*
 * kernel/printk.c
 *
 * Copyright (c) 2015, Armand Zangue <armand@zangue.com>
 */

#include <stdarg.h>
#include <osirix/vsprintf.h>

void printk(char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	vsprintf(fmt, ap);
	va_end(ap);
}
