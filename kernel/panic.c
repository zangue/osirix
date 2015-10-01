/*
 * panic.c
 *
 * This file is part of Embedded-OS
 *
 * Copyrigth (c) 2015, Armand Zangue <armand@zangue.com>
 */

 #include "printk.h"

__attribute__((noreturn))
void panic(const char * s)
{
	printk("Kernel panic: %s\n\r",s);
 	while(1)
		continue;
}
