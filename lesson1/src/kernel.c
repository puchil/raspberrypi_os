#include "mini_uart.h"
#include "mailbox.h"

void print_serial_num()
{
	// get the board's unique serial number with a mailbox call
    mbox[0] = 8*4;                  // length of the message
    mbox[1] = MBOX_REQUEST;         // this is a request message
    mbox[2] = MBOX_TAG_GETSERIAL;   // get serial number command
    mbox[3] = 8;                    // buffer size
    mbox[4] = 8;
    mbox[5] = 0;                    // clear output buffer
    mbox[6] = 0;
    mbox[7] = MBOX_TAG_LAST;

    if(mbox_call(MBOX_CH_PROP)){
	    uart_send_string("Serial Number: ");
	    uart_send_hex(mbox[6]);
	    uart_send_hex(mbox[5]);
    } else {
    	uart_send_string("Error: Unable to query Serial Number!");
    }
}

void kernel_main( void )
{
	uart_init();
	uart_send_string("Hello, Minix 4!\n");
	print_serial_num();
	while(1)
		uart_send(uart_recv());
}
