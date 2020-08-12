#ifndef	_P_UART_H
#define	_P_UART_H

#include "peripherals/base.h"

/* PL011 UART registers */
#define UART0_BASE  PBASE+0x00201000

//Name				Offset	  			Type	Description
#define UARTDR		UART0_BASE+0x000 	//RW	Data Register, UARTDR
#define UARTRSR_ECR	UART0_BASE+0x004	//RW	Receive Status Register / Error Clear Register, UARTRSR/UARTECR
#define UARTFR		UART0_BASE+0x018	//RO	Flag Register, UARTFR
#define UARTILPR	UART0_BASE+0x020	//RW	IrDA Low-Power Counter Register, UARTILPR
#define UARTIBRD	UART0_BASE+0x024	//RW	Integer Baud Rate Register, UARTIBRD
#define UARTFBRD	UART0_BASE+0x028	//RW	Fractional Baud Rate Register, UARTFBRD
#define UARTLCRH	UART0_BASE+0x02C	//RW	Line Control Register, UARTLCR_H
#define UARTCR		UART0_BASE+0x030	//RW	Control Register, UARTCR
#define UARTIFLS	UART0_BASE+0x034	//RW	Interrupt FIFO Level Select Register, UARTIFLS
#define UARTIMSC	UART0_BASE+0x038	//RW	Interrupt Mask Set/Clear Register, UARTIMSC
#define UARTRIS		UART0_BASE+0x03C	//RO	Raw Interrupt Status Register, UARTRIS
#define UARTMIS		UART0_BASE+0x040	//RO	Masked Interrupt Status Register, UARTMIS
#define UARTICR		UART0_BASE+0x044	//WO	Interrupt Clear Register, UARTICR
#define UARTDMACR	UART0_BASE+0x048	//RW	DMA Control Register, UARTDMACR
//define UARTPeriphID0	0xFE0	RO	UARTPeriphID0 Register
//define UARTPeriphID1	0xFE4	RO	UARTPeriphID1 Register
//define UARTPeriphID2	0xFE8	RO	UARTPeriphID2 Register
//define UARTPeriphID3	0xFEC	RO	UARTPeriphID3 Register
//define UARTPCellID0	0xFF0	RO	UARTPCellID0 Register
//define UARTPCellID1	0xFF4	RO	UARTPCellID1 Register
//define UARTPCellID2	0xFF8	RO	UARTPCellID2 Register
//define UARTPCellID3	0xFFC	RO	UARTPCellID3 Register

#endif  /*_P_UART_H */