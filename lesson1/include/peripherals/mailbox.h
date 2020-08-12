#include "base.h"

#define MAIL_BASE 		(PBASE+0x0000B880)	// Base address for the mailbox registers

#define MBOX_READ       (MAIL_BASE+0x0)
#define MBOX_POLL       (MAIL_BASE+0x10)
#define MBOX_SENDER     (MAIL_BASE+0x14)
#define MBOX_STATUS     (MAIL_BASE+0x18)
#define MBOX_CONFIG     (MAIL_BASE+0x1C)
#define MBOX_WRITE      (MAIL_BASE+0x20)

#define MBOX_RESPONSE   0x80000000
#define MBOX_FULL       0x80000000
#define MBOX_EMPTY      0x40000000