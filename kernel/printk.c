/*
 * printk.c
 *
 * This file is part of Embedded-OS
 *
 * Copyright (c) 2015, Armand Zangue <armand@zangue.com>
 */

#include <stdarg.h>
#include "vsprintf.h"

void printk(char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	vsprintf(fmt, ap);
	va_end(ap);
}
