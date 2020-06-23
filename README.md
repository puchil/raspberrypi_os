# Porting Minix to Raspberry Pi

As an software engineer, I want to learn all the parts of an OS. Rather than implementing a new OS 101, I feel the best way to learn would be to use an existing OS and port to a hardware.

## Goal (My thoughts)
1. Port Minix to Raspberry Pi 4.
1. Make it usable wih all programming tools and a GUI
1. Port Minix to all other Raspberry Pi models
1. Easy install on Raspberry Pi
1. Allow minimal and full stack of Raspberry Pi
   1. Minimal: Just the base kernel and few utils
   1. Full: All tools and utils with a full blown GUI

## Tasks (ToDo)

Sl. | Details | Status
----|---------|---------
1. | SD Card Support | Incomplete
2. | HDMI/Mini HDMI Support | Incomplete
3. | USB/Micro USB Support | Incomplete
4. | 64 Bit Kernel Support | Incomplete
5. | SMP Support | Incomplete

## What work needs to be done?:
__copied from "The future of Minix." posted in minix3 google group by "stux atMinix"__

Here is a list of some of the most crucial items to erase some of Minix's technical debt:
* Fix cross-compilation issues in Debian [https://github.com/Stichting-MINIX-Research-Foundation/minix/issues/229].  This is the most common cross-compilation platform.  Changes in gcc seem to be preventing users from simply running the release tools with no modification.
* Enable user thread support on pkgsrc packages.  Most modern software now assumes that operating systems provide native thread support. Minix does not. Instead, packages need to be automatically compiled and built while using userspace threading libraries available in Minix.  I've been told pkgsrc is supposed to automatically do this, but for some reason it's broken in Minix.  This prevents modern packages from building in Minix due to dependencies (for example: all packages that depend on a modern version of python won't build if python itself won't build). 
* Bring Minix's userland up to par with current NetBSD [https://github.com/Stichting-MINIX-Research-Foundation/minix/issues/258].  This is not a straightforward process and this was previously conducted by a volunteer.  This may in some way be related to the pkgsrc/threading issue I mentioned above. 
* Complete work for Clang Support on ARM [https://github.com/Stichting-MINIX-Research-Foundation/minix/pull/195].  This is one of those loose threads that doesn't prevent a release but would be nice to finish up.  On x86 Minix uses the clang compiler to build its code.  However, on ARM there were technical reasons that forced builds to use gcc to build its code.  The linked pull request fixes that.  However there are a few tests that fail which need to be resolved before the pull request can be pushed to the master branch.

Here is a list of lower-priority items that nevertheless need to be implemented in order to turn Minix into a modern OS and fully erase its technical debt. Some and more of these items can be found in the Wishlist [https://wiki.minix3.org/doku.php?id=wishlist:start], David's wishlist [https://wiki.minix3.org/doku.php?id=wishlist:david] and Roadmap [https://wiki.minix3.org/doku.php?id=roadmap]:
* Complete and merge work done on a Raspberri Pi port of Minix [https://github.com/Stichting-MINIX-Research-Foundation/minix/pull/134] from GSOC 2017[https://wiki.minix3.org/doku.php?id=soc:2017:start].  This work is important because there were improvements made to the kernel that made it more generic and easier to port to new platforms. This would likely facilitate several of the items listed below.
* Port Minix to x64 [https://wiki.minix3.org/doku.php?id=soc:2018:start].  This was a proposed GSOC that never received funding.  Minix only builds on x86 and runs on x64 under emulation. This port would allow Minix to run natively on x64 and use all of the RAM available in the system.  The caveat is that PAE support is required in x64 (which Minix does not have) and there may be minor issues with pointer types in some parts of the code.
* Add kernel thread support. This is a bigger issue than it sounds.  Currently, each process can support only a single thread and would emulate multiple threads using user libraries.  Unfortunately, this has performance implications since any single blocking operation (such as I/O) blocks all threads.  Not only the kernel, but all servers have to be updated to support a platform where a process can have multiple threads each blocking independently.
* RUMP support: Supporting the RUMP kernel [https://en.wikipedia.org/wiki/Rump_kernel] has the potential of allowing Minix to use all or most of NetBSD's drivers with little porting necessary.  This is why it's listed in both the 2017 and 2018 GSOC proposals.
* USB Support:  another big requirement since all modern hardware depends on USB.  USB development was explored but no implementations are available.  As I understand it there are other requirements (such as ACPI and APIC support) that need to be met.  It is the hope that RUMP can provide these for free or cheap-as-free.
* Add SMT Support: who doesn't like multi-core architectures?  Minix can only run on one CPU and we need to change that. There is a pull request [https://github.com/Stichting-MINIX-Research-Foundation/minix/pull/292] that attempts just that but it hasn't been pushed to master, let alone thoroughly vetted and tested.  If threading support is implemented, these changes may need to be revisited.
* Implement Job Control [https://wiki.minix3.org/doku.php?id=wishlist:david] - this is necessary to get all the POSIX goodies [https://en.wikipedia.org/wiki/Job_control_%28Unix%29] people are used to such as process grouping.
* Security Hardening Minix: code audits, security audits, and eventual formal verification like SEL4 should also be a long term goal.  Due to technical debt, Minix may vulnerable to exploits that have already been secured in other OSes. Some of the speculative execution vulnerabilities come to mind (though the Minix microkernel architecture itself may naturally prevent some of these).  Minix's service model means people have to jump more hoops to do something nasty to the OS.  But if minix were to gain popularity, it would get the same scrutiny as mainstream OSes and have those extra hoops discovered.

This list is long but not exhaustive. None of the items are simple either.  However, tackling the above items should bring Minix nearly on par with NetBSD's software and hardware support. For those who are not aware: Minix adopted NetBSD's userland in order to allow developers to focus on the Microkernel architecture itself.  Among other things, RUMP was believed to be the right approach to abstracting hardware support from the kernel architecture and one of the factors in deciding which BSD's userspace to adopt.  However, that doesn't mean tools from the other major BSDs can't be used. But being able to virtually replace the NetBSD kernel with Minix's architecture was the eventual goal behind this decision.