#ifndef _UART_H
#define _UART_H

void uart_init(void);
unsigned char uart_rx(void);
void uart_tx(unsigned char byte);
#endif /* _UART_H */
