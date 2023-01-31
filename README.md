# S100 Pi Zero Z80  Project.
A pi zero z80 emulator running on s100 bus 

NOTE:  You will need the WireingPi repo in order to run this code.
https://github.com/WiringPi/WiringPi.git

This project ports z80core so it will run on Pi Zero and use the s100 bus hardware.

The z80core code is from Udo Munk's z80pack repo. https://www.autometer.de/unix4fun/z80pack/
I started this adventure with the goal of creating a z80 simulator (or parts there of) enough
to boot CP/M off the CFCard controller.  My attemp to create a z80 simulator was laughable 
at best.  I then ported a major part of z80core to my simulator (sim1 through sim6) and
I find that so far the simulator works just fine.  I can boot the system prom and run
commands on the s100 h/w.  However at this time, I can't boot CP/M.  I get a disk timeout.

A comment on fidelity.  We will not likely be able to produce exactly the I/O process
that the z80 does.  I'm thinking about the upper 8 address bits during the OTIR etc.
instructions.  This may have some side effects latter on.

This is still WIP.  It will run the MASTER0 boot prom up to the '->' prompt. 

To build this code.
git clone 

