#include "utils.h"
#include "peripherals/mailbox.h"

/*
Logic derived from
https://github.com/raspberrypi/documentation/blob/JamesH65-mailbox_docs/configuration/mailboxes/accessing.md
https://github.com/bztsrc/raspi3-tutorial/blob/master/04_mailboxes/mbox.c
*/

/*
 * To read from a mailbox:
 *  - Read the status register until the empty flag is not set
 *  - Read data from the read register
 *  - If the lower four bits do not match the channel number desired then repeat from 1
 *  - The upper 28 bits are the returned data
 */
unsigned int read_mbox(unsigned char channel)
{
	while(1) {
		do{
			asm volatile("nop");
		} while((get32(MBOX_STATUS)&MBOX_EMPTY) != 0);
		unsigned int data = get32(MBOX_READ);
		unsigned char readChannel = data & 0xF;
		data >>= 4;
		if(readChannel == channel)
			return data;
	}
}


/*
 * To write to a mailbox
 *  - Read the status register until the full flag is not set
 *  - Write the data (shifted into the upper 28 bits) combined with the channel 
 *    (in the lower four bits) to the write register
 */
void write_mbox(unsigned char channel, unsigned int data)
{
	do{
		asm volatile("nop");
	} while((get32(MBOX_STATUS)&MBOX_FULL) != 0);
	put32(MBOX_WRITE, data|(channel&0xF));
}

/* mailbox message buffer */
volatile unsigned int  __attribute__((aligned(16))) mbox[36];

int call_mbox(unsigned char channel)
{
	unsigned int data = (((unsigned int)((unsigned long)&mbox)&~0xF));
	write_mbox(channel, data);
	data = read_mbox(channel);
	return(mbox[1]==MBOX_RESPONSE);
}