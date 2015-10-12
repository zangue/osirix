#ifndef _OSIRIX_KERNEL_H
#define _OSIRIX_KERNEL_H

/* System clock frequency */
#define SYS_HZ 250000000

__attribute__ ((format(printf,1,2)))
void vsprintf(const char *fmt, ...);
__attribute__ ((format(printf,1,2)))
void printk(const char *fmt, ...);
__attribute__ ((noreturn format(printf,1,2)))
void panic(const char *fmt, ...);
#endif /* _OSIRIX_KERNEL_H */
