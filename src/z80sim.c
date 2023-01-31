/* simulate a z80 cpu in this code */

#include <stdlib.h>
#include <stdio.h>
#include "z80sim.h"
#include <ctype.h>

unsigned char Instruction;
extern unsigned short PC;
extern void s100_init ();
extern int TraceFlag;
extern int TraceReg;
extern void PrintInstruction ();
extern void LoadBootRom ();
extern void SnapShot ();
extern void DumpReg ();
extern int parity[];
extern void WriteRAM ();
extern char ReadRAM ();
extern void WritePort ();
extern char ReadPort ();
unsigned int BreakAddr;
unsigned int low,mid,high;
extern void cpu_z80();

#define FETCHBYTE(a) {Low = ReadRAM(a++);}
#define FETCHADDR(a) {Low = ReadRAM(a++); High = ReadRAM(a++);}
#define TRACE(a,b,c) {PrintInstruction(a,b,c);}
#define DEC(a,b) {if(b==0x0) a--;b--;}
#define INC(a,b) {if(b==0xff)a++;b++;}
#define PATCH(a,b) { WriteRAM(a,b);}

/* push pop code */

void
Push (unsigned char hi, unsigned char low)
{
  WriteRAM (StackPointer - 2, low);
  WriteRAM (StackPointer - 1, hi);
  StackPointer -= 2;
}

void
Pop (unsigned char *hi, unsigned char *low)
{
  *hi = ReadRAM (StackPointer + 1);
  *low = ReadRAM (StackPointer);
  StackPointer += 2;
}

/* compair the bytes and set the flags as needed */

/*   C  carry flag
     N  add/subtract 
     P/V Parity/Overflow flag
     H  half cary flag
     Z  zero flag
     S  sign flag
*/
void
Compair (unsigned char A, unsigned char P)
{
  register int i;

  ((P & 0xf) > (A & 0xf)) ? (CpuStatus |= HFlag) : (CpuStatus &= ~HFlag);
  (P > A) ? (CpuStatus |= CFlag) : (CpuStatus &= ~CFlag);
  i = (signed char) A - (signed char) P;
  (i < -128 || i > 127) ? (CpuStatus |= PFFlag) : (CpuStatus &= ~PFFlag);
  (i & 128) ? (CpuStatus |= SFlag) : (CpuStatus &= ~SFlag);
  (i) ? (CpuStatus &= ~ZFlag) : (CpuStatus |= ZFlag);
  CpuStatus |= NFlag;
}


void
main (int argc, char *argv[])
{
  int i;
  unsigned char h, l;

/* initialize the s100 bus hardware */
  s100_init ();
/* set up address banking code */
/* these are all illegal values that will be updated on the
first address assertion */

	low = 1000;
	mid = 1000;
	high = 1000;

/* load the boot prom code into ReadRAM at 0xe000 and start it.
of course, on the real hardware we will just start running at 0xe000 since
the boot prom is located in our address space. */
  LoadBootRom ();
PATCH(0xe45f,0);
PATCH(0xe460,0);
PATCH(0xe46c,0xc9);
  PC = RUN_BASE;
#ifdef BREAK
  BreakAddr = 0xe1b5;
#endif
#ifdef TRACEF
  TraceFlag = 1;
  TraceReg = 1;
#endif
  cpu_z80();
}
