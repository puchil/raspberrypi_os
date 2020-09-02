#ifndef	_P_IRQ_H
#define _P_IRQ_H

#include "peripherals/base.h"

#define ARMC_BASE (PBASE+0x0000B000)

#define IRQ0_PENDING0 (ARMC_BASE+0x200) //ARM Core 0 IRQ Enabled Interrupt Pending bits [31:0]
#define IRQ0_PENDING1 (ARMC_BASE+0x204) //ARM Core 0 IRQ Enabled Interrupt pending bits [63:32]
#define IRQ0_PENDING2 (ARMC_BASE+0x208) //ARM Core 0 IRQ Enabled Interrupt pending bits [79:64]
#define IRQ0_SET_EN_0 (ARMC_BASE+0x210) //Write to Set ARM Core 0 IRQ enable bits [31:0]
#define IRQ0_SET_EN_1 (ARMC_BASE+0x214) //Write to Set ARM Core 0 IRQ enable bits [63:32]
#define IRQ0_SET_EN_2 (ARMC_BASE+0x218) //Write to Set ARM Core 0 IRQ enable bits[79:64]
#define IRQ0_CLR_EN_0 (ARMC_BASE+0x220) //Write to Clear ARM Core 0 IRQ enable bits [31:0]
#define IRQ0_CLR_EN_1 (ARMC_BASE+0x224) //Write to Clear ARM Core 0 IRQ enable bits [63:32]
#define IRQ0_CLR_EN_2 (ARMC_BASE+0x228) //Write to Clear ARM Core 0 IRQ enable bits [79:64]
#define IRQ_STATUS0   (ARMC_BASE+0x230) //Interrupt Line bits [31:0]
#define IRQ_STATUS1   (ARMC_BASE+0x234) //Interrupt Line bits [63:32]
#define IRQ_STATUS2   (ARMC_BASE+0x238) //Interrupt Line bits [79:64]

#define SYSTEM_TIMER_IRQ_0	(1 << 0)
#define SYSTEM_TIMER_IRQ_1	(1 << 1)
#define SYSTEM_TIMER_IRQ_2	(1 << 2)
#define SYSTEM_TIMER_IRQ_3	(1 << 3)

#endif