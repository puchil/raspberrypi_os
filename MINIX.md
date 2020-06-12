# How MINIX works?

Summary from the book "Operating Systems Design Implementation 3"

## MINIX3 System Components
Component|Description                              |Loaded by
kernel   |Kernel + clock and system tasks          |(in boot image)
pm       |Process manager                          |(in boot image)
fs       |File system                              |(in boot image)
rs       |(Re)starts servers and drivers           |(in boot image)
memory   |RAM disk driver                          |(in boot image)
log      |Buffers log output                       |(in boot image)
tty      |Console and keyboard driver              |(in boot image)
driver   |Disk (at, bios, or floppy) driver        |(in boot image)
init     |parent of all user processes             |(in boot image)
floppy   |Floppy driver (if booted from hard disk) |/etc/rc
is       |Information server (for debug dumps)     |/etc/rc
cmos     |Reads CMOS clock to set time             |/etc/rc
random   |Random number generator                  |/etc/rc
printer  |Printer driver                           |/etc/rc