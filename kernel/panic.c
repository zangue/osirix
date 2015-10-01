/*
 * kernel/panic.c
 *
 * Copyrigth (c) 2015, Armand Zangue <armand@zangue.com>
 */

 #include <osirix/printk.h>

//TODO
__attribute__((noreturn))
void panic(const char * s)
{
	printk("Kernel panic: %s\n\r",s);
 	while(1)
		continue;
}
