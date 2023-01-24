# S100 Pi Zero Z80  Project.
A pi zero z80 emulator running on s100 bus 

NOTE:  You will need the WireingPi repo in order to run this code.
https://github.com/WiringPi/WiringPi.git

This project is an attempt to create a z80 emulator running on s100 bus hardware.

A comment on fidelity.  We will not likely be able to produce exactly the I/O process
that the z80 does.  I'm thinking about the upper 8 address bits during the OTIR etc.
instructions.  This may have some side effects latter on.

This is still WIP.  It will run the MASTER0 boot prom up to the '->' prompt.  After
that any command will cause a crash due to stack alignment issues.
