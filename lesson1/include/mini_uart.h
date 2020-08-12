#ifndef	_MINI_UART_H
#define	_MINI_UART_H

void miniuart_init ( void );
char miniuart_recv ( void );
void miniuart_send ( char c );
void miniuart_send_string(char* str);
void miniuart_send_hex(unsigned int d);

#endif  /*_MINI_UART_H */