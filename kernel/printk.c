/*
 * kernel/printk.c
 *
 * Copyright (c) 2015, Armand Zangue
 */

#include <stdarg.h>
#include <osirix/kernel.h>

void printk(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	vsprintf(fmt, ap);
	va_end(ap);
}
