# How MINIX works?

Summary from the book "Operating Systems Design Implementation 3"

## MINIX3 System Components
Component|Description                              |Loaded by      |Comments
---------|-----------------------------------------|---------------|---------
kernel   |Kernel + clock and system tasks (No PID) |(in boot image)|
pm       |Process manager (PID=0, SOLO*)           |(in boot image)|
fs       |File system                              |(in boot image)|
rs       |(Re)starts servers and drivers           |(in boot image)|
memory   |RAM disk driver                          |(in boot image)|
log      |Buffers log output                       |(in boot image)|
tty      |Console and keyboard driver              |(in boot image)|
driver   |Disk (at, bios, or floppy) driver        |(in boot image)|
init     |Mother of all user processes             |(in boot image)|PID=1,PARENT=rs
floppy   |Floppy driver (if booted from hard disk) |/etc/rc        |
is       |Information server (for debug dumps)     |/etc/rc        |produced by function keys
cmos     |Reads CMOS clock to set time             |/etc/rc        |
random   |Random number generator                  |/etc/rc        |
printer  |Printer driver                           |/etc/rc        |
service  |Service is the user interface to the reincarnation server.|/etc/rc|

SOLO: neither a child nor a parent of any other process

## rs - Reincarnation Server
* The reincarnation server is made the parent of all the other processes started from the boot image (e.g., the drivers and servers). The reincarnation server is informed if any of these should need to be restarted.
* The reincarnation server starts an ordinary program and converts it into a system process.
* One of the actions of the reincarnation server is to adopt all system processes except the process manager as its own children.

## init - Mother of all user processes
* init first executes the /etc/rc shell script. (Run Control Scripts)
* This script starts additional drivers and servers that are not part of the boot image.
* Any program started by the rc script will be a child of init.
* One of the first programs run is a utility called service.
* An important function of the rc script is to check for file system problems that might have resulted from a previous system crash. The test is simplewhen the system is shutdown correctly by executing the shutdown command an entry is written to the login history file, /usr/adm/wtmp. The command ```shutdown C``` checks whether the last entry in wtmp is a shutdown entry. If not, it is assumed an abnormal shutdown occurred, and the ```fsck``` utility is run to check all file systems. 
* The final job of /etc/rc is to start daemons. This may be done by subsidiary scripts. If you look at the output of a ```ps axl``` command, which shows both PIDs and parent PIDs (PPIDs), you will see that daemons such as update and usyslogd will normally be the among the first persistent processes which are children of init.
* Finally init reads the file /etc/ttytab, which lists all potential terminal devices. Those devices that can be used as login terminals (in the standard distribution, just the main console and up to three virtual consoles, but serial lines and network pseudo terminals can be added) have an entry in the getty field of /etc/ttytab, and init forks off a child process for each such terminal. Normally, each child executes /usr/bin/getty which prints a message, then waits for a name to be typed. If a particular terminal requires special treatment (e.g., a dial-up line) /etc/ttytab can specify a command (such as /usr/bin/stty) to be executed to initialize the line before running getty.

## fs - File System
```/sbin``` - The servers and drivers needed initially
```/bin```  - Other commands needed for startup

## System Calls
### Process Management
* When a program is executed, it is allocated a portion of memory whose size is specified in the program file's header. It keeps this amount of memory throughout its execution, although the distribution among data segment, stack segment, and unused can vary as the process runs.
* All the information about a process is kept in the process table, which is divided up among the kernel, process manager, and file system, with each one having those fields that it needs. When a new process comes into existence (by ```fork```), or an old process terminates (by ```exit``` or a ```signal```), the process manager first updates its part of the process table and then sends messages to the file system and kernel telling them to do likewise.

Call|Details
----|------------------------------------------------
Fork|is the only way to create a new process. 
Exec|allows a process to execute a specified program.

### Interprocess Communication
* The second parameter in each call is the local address of the message data. The message passing mechanism in the kernel copies the message from the sender to the receiver. The reply (for sendrec) overwrites the original message.
* Each task, driver or server process is allowed to exchange messages only with certain other processes. 
* The usual flow of messages is downward in the layers, and messages can be between processes in the same layer or between processes in adjacent layers. User processes cannot send messages to each other. E.g. User processes in layer 4 can initiate messages to servers in layer 3, servers in layer 3 can initiate messages to drivers in layer 2.
* When a process sends a message to a process that is not currently waiting for a message, the sender blocks until the destination does a receive. The advantage of this approach is that it is simple and eliminates the need for buffer management (including the possibility of running out of buffers). In addition, because all messages are of fixed length determined at compile time, buffer overrun errors, a common source of bugs, are structurally prevented.
* A notify is nonblocking, which means the sender continues to execute whether or not the recipient is waiting. Because it does not block, a notification avoids the possibility of a message deadlock.

Call|Details
----|------------------------------------------------
send(dest, &message);|send a message to process dest
receive(source, &message);|receive a message from process source (or ANY)
sendrec(src_dst, &message);|send a message and wait for a reply from the same process
notify(dest)|same as send, but nonblocking