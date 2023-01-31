# S100 Pi Zero Z80  Project.
A pi zero z80 emulator running on s100 bus, here is the hardware link http://www.s100computers.com/My%20System%20Pages/Raspberry%20Pi%20CPU%20Board/Raspberry%20Pi%20CPU%20Board.htm

NOTE:  You will need the WireingPi repo in order to run this code.
https://github.com/WiringPi/WiringPi.git

This project ports z80core so it will run on Pi Zero and use the s100 bus hardware.

The z80core code is from Udo Munk's z80pack repo. https://www.autometer.de/unix4fun/z80pack/
I started this adventure with the goal of creating a z80 simulator (or parts there of) enough
to boot CP/M off the CFCard controller.  My attempt to create a z80 simulator was laughable 
at best.  I then ported a major part of z80core to my simulator (sim1 through sim6) and
I find that so far the simulator works just fine.  I can boot the system prom and run
commands on the s100 h/w.  However at this time, I can't boot CP/M.  I get a disk timeout.

A comment on fidelity.  We will not likely be able to produce exactly the I/O process
that the z80 does.  I'm thinking about the upper 8 address bits during the OTIR etc.
instructions.  This may have some side effects latter on.

This is still WIP.  It will run the MASTER0 boot prom up to the '->' prompt. 

```
To build this code.
git clone https://github.com/jayacotton/s100pizeroz80.git
git clone https://github.com/WiringPi/WiringPi.git

cd WireingPi
./build

cd s100pizeroz80/src
make

./z80sim
```
NOTE: there are a number of compile options for this code.  Many are there for debugging
the simulator, some are there to improve performance.  Look at the Makefile for clues.

A note on performance.  In a word, don't expect it to be fast.  As best as I can figure, the simulator
is running at about 500khz.  This is not the fault of z80core, it is known to run very fast.
Nor does it seem to be interfaceing with the s100 bus.  Althow I can get a slight increase in
speed by using local ram for the program storage.  I have not in fact found the source of
the speed issues, but I suspect that the Pi Zero is not up to the task.

```
Architecture:          armv6l
Byte Order:            Little Endian
CPU(s):                1
On-line CPU(s) list:   0
Thread(s) per core:    1
Core(s) per socket:    1
Socket(s):             1
Model:                 7
Model name:            ARMv6-compatible processor rev 7 (v6l)
CPU max MHz:           1000.0000
CPU min MHz:           700.0000
BogoMIPS:              997.08
Flags:                 half thumb fastmult vfp edsp java tls
```


