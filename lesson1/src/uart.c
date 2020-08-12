/*uart.c*/
#include "utils.h"
#include "mailbox.h"
#include "peripherals/uart.h"
#include "peripherals/gpio.h"

void uart_send( char c )
{
	while(1){
		if(get32(UARTFR)&0x20)
			break;
	}
	put32(UARTDR, c);
}

// This function is required by printf function
void putc ( void* p, char c)
{
	uart_send(c);
}

void uart_send_string(char* str)
{
	for(int i=0; str[i] != '\0'; i++)
		uart_send((char)str[i]);
}

/**
 * Display a binary value in hexadecimal
 */
void uart_send_hex(unsigned int d) {
    unsigned int n;
    int c;
    for(c=28;c>=0;c-=4) {
        // get highest tetrad
        n=(d>>c)&0xF;
        // 0-9 => '0'-'9', 10-15 => 'A'-'F'
        n+=n>9?0x37:0x30;
        uart_send(n);
    }
}

char uart_recv( void )
{
	while(1){
		if(get32(UARTFR)&0x10)
			break;
	}
	return(get32(UARTDR)&0xFF);
}

void setup_clock( void )
{
	/* set up clock for consistent divisor values */
    mbox[0] = 9*4;
    mbox[1] = MBOX_REQUEST;
    mbox[2] = MBOX_TAG_SETCLKRATE; // set clock rate
    mbox[3] = 12;
    mbox[4] = 8;
    mbox[5] = 2;           // UART clock
    mbox[6] = 4000000;     // 4Mhz
    mbox[7] = 0;           // clear turbo
    mbox[8] = MBOX_TAG_LAST;
    call_mbox(MBOX_CH_PROP);
}


void uart_init( void )
{
	put32(UARTCR, 0);			// turn off UART0
	setup_clock();

	unsigned int selector;
	selector = get32(GPFSEL1);
	selector &= ~(7<<12);		// clean gpio14
	selector |= 2<<12;			// set alt5 for gpio14
	selector &= ~(7<<15);		// clean gpio15
	selector |= 2<<15;			// set alt5 for gpio15
	put32(GPFSEL1, selector);

	put32(GPPUD, 0);
	delay(150);
	put32(GPPUDCLK0, (1<<14)|(1<<15));
	delay(150);
	put32(GPPUDCLK0,0);

	put32(UARTICR,0x7FF);		// Clear Interrupts
	put32(UARTIBRD,2);			// Baud Rate = 115200
	put32(UARTFBRD,0xB);
	put32(UARTLCRH,0b11<<5);	// 8n1
	put32(UARTCR,0x301);		// enable Tx, Rx, FIFO
}