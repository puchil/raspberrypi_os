#include "mini_uart.h"
#include "mailbox.h"
#include "printf.h"
#include "utils.h"
#include "timer.h"
#include "irq.h"

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

    if(call_mbox(MBOX_CH_PROP)){
	    printf("Serial Number: %x-%x", mbox[6], mbox[5]);
    } else {
    	printf("Error: Unable to query Serial Number!");
    }
}

void kernel_main( void )
{
	miniuart_init();
    init_printf(0, miniuart_putc);

    miniuart_send_string("Hello, Minix 4 Kernel!\r\n");
    int el = get_el();
	printf("Running at Exception Level %d.\r\n", el);
	print_serial_num();

    irq_vector_init();
    timer_init();
    enable_interrupt_controller();
    enable_irq();

    printf("\r\niEcho: ");
	while(1)
		miniuart_send(miniuart_recv());
}
