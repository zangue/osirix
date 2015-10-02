/*
 * kernel/panic.c
 *
 * Copyrigth (c) 2015, Armand Zangue <armand@zangue.com>
 */

#include <stdarg.h>
#include <osirix/kernel.h>

//TODO
__attribute__((noreturn format(printf,1,2)))
void panic(const char *fmt, ...)
{
	//printk("Kernel panic: %s\n\r", fmt);
	va_list ap;

	va_start(ap, fmt);
	vsprintf(fmt, ap);
	va_end(ap);
 	
	while(1)
		continue;
}
