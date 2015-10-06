#ifndef _AUX_H
#define _AUX_H

#include <stddef.h>
#include <stdint.h>

/* AUX base address - Broadcom BCM2835 */
#define AUX_BASE 0x20215000

#define MU_IRQ		(1 << 0)
#define SPI1_IRQ	(1 << 1)
#define SPI2_IRQ	(1 << 2)

#define MU_ENABLE	(1 << 0)
#define SPI1_ENABLE	(1 << 1)
#define SPI2_ENABLE	(1 << 2)


struct aux {
	unsigned int irq;	/* Auxiliary interrupt status */
	unsigned int enables;	/* Auxiliary enables */
	unsigned int unused1[((0x40 - 0x04) / 4) - 1]
	unsigned int mu_io_reg;	/* Mini Uart I/O data */
	unsigned int mu_ier_reg; /* Mini Uart interrupt enable */
	unsigned int mu_iir_reg; /* Mini Uart interrupt indentify */
	unsigned int mu_lcr_reg; /* Mini Uart line control */
	unsigned int mu_mcr_reg; /* Mini Uart modem control */
	unsigned int mu_lsr_reg; /* Mini Uart line status */
	unsigned int mu_msr_reg; /* Mini Uart modem status */
	unsigned int mu_scratch; /* Mini Uart scratch */
	unsigned int mu_cntl_reg; /* Mini Uart extra control */
	unsigned int mu_stat_reg; /* Mini Uart extra status */
	unsigned int mu_baud_reg; /* Mini Uart baudrate */
	unsigned int unused2[(0x80 - 0x68) / 4];
	unsigned int spi0_ctnl0_reg; /* SPI 1 control register 0 */
	unsigned int spi0_ctnl1_reg; /* SPI 1 control register 1 */
	unsigned int spi0_stat_reg; /* SPI 1 status */
	unsigned int spi0_io_reg; /* SPI 1 data */
	unsigned int spi0_peek_reg; /* SPI 1 Peek */
	unsigned int unused3[(0xC0 - 0x94) / 4];
	unsigned int spi1_ctnl0_reg; /* SPI 2 control register 0 */
	unsigned int spi1_ctnl1_reg; /* SPI 2 control register 1 */
	unsigned int spi1_stat_reg; /* SPI 2 status */
	unsigned int spi1_io_reg; /* SPI 2 data */
	unsigned int spi1_peek_reg; /* SPI 2 Peek */
};


#endif /* _AUX_H */
