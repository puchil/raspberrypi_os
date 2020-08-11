#include "utils.h"
#include "peripherals/mini_uart.h"
#include "peripherals/gpio.h"

void uart_send( char c )
{
	while(1){
		if(get32(AUX_MU_LSR_REG)&0x20)
			break;
	}
	put32(AUX_MU_IO_REG, c);
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
		if(get32(AUX_MU_LSR_REG)&0x01)
			break;
	}
	return(get32(AUX_MU_IO_REG)&0xFF);
}


void uart_init( void )
{
	unsigned int selector;
	selector = get32(GPFSEL1);
	selector &= ~(7<<12);		//clean gpio14
	selector |= 2<<12;			//set alt5 for gpio14
	selector &= ~(7<<15);		//clean gpio15
	selector |= 2<<15;			//set alt5 for gpio15
	put32(GPFSEL1, selector);

	put32(GPPUD, 0);
	delay(150);
	put32(GPPUDCLK0, (1<<14)|(1<<15));
	delay(150);
	put32(GPPUDCLK0,0);

	put32(AUX_ENABLES,1);       //Enable mini uart (this also enables access to it registers)
	put32(AUX_MU_CNTL_REG,0);   //Disable auto flow control and disable receiver and transmitter (for now)
	put32(AUX_MU_IER_REG,0);    //Disable receive and transmit interrupts
	put32(AUX_MU_LCR_REG,3);    //Enable 3=8 bit mode/2=7 bit
	put32(AUX_MU_MCR_REG,0);    //Set RTS line to be always high
	unsigned int baudrate = 115200;
	unsigned int baudreg  = 500000000 / (8 * baudrate) - 1;
	put32(AUX_MU_BAUD_REG,baudreg); //Set baud rate to 115200

	put32(AUX_MU_CNTL_REG,3);   //Finally, enable transmitter and receiver
}