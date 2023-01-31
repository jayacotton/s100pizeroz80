/* utility code for the z80 simulator */

/* all the stuff that we need for running debug on a LINUX system
without the hardware connected */

#include <stdio.h>
#include <stdlib.h>
#include "z80sim.h"
#include "sim.h"
#include "simglb.h"
int TraceFlag;
int TraceReg;

extern unsigned int BreakAddr;
extern void WriteRAM ();
extern unsigned char ReadRAM ();
extern OPCODES OpCodeList[];

#ifdef LINUX

FILE *in;

  unsigned char localram[64 * 1024];

void
LoadBootRom ()
{
  unsigned char *loadpoint;
  int i;
	unsigned char a,b;
int size;

  if (TraceFlag)
    printf ("read and load the boot rom code\n");

  loadpoint = &localram[0x100];
  in = fopen ("MASTER0.COM", "r");
  if (in == 0)
    {
      printf ("can open boot rom\n");
      exit (0);
    }
  size = fread (loadpoint, 1, 1024*64, in);
  for (i = RUN_BASE; i < (size+0x100); i++)
    {
	a = localram[i];
      WriteRAM (i, localram[i]);
	b = ReadRAM(i);
	if(a != b){
		printf("LoadBootRom:Readback failed %04x %02x %02x\n",i,a,b);
	}
    }
  fclose (in);
}
#else
#endif

/* all the utility code that will work without the s100 h/w connected */

/* trace instruction at address */

void
PrintInstruction (unsigned short addr, int size, int level)
{
  struct OpCodes *ptr;

/* address is the current address of PCAddress */
/* size is the number of bytes to print for this instruction */
/* level is the depth index for the instruction decode */


  if (TraceFlag)
    {
      ptr = &OpCodeList[(unsigned int) ReadRAM (addr)];
/* deal with special case instructions */
      switch (ReadRAM (addr))
	{
	case 0xcb:
	  printf ("%04x %02x %02x\t", addr, ReadRAM (addr),
		  ReadRAM (addr + 1));
	  ptr = &OpCodeList[(unsigned int) ReadRAM (addr + 1)];
	  printf ("%s\n", ptr->code3);
	  break;
	case 0xdd:
	  printf ("%04x %02x %02x\t", addr, ReadRAM (addr),
		  ReadRAM (addr + 1));
	  ptr = &OpCodeList[(unsigned int) ReadRAM (addr + 1)];
	  printf ("%s\n", ptr->code2);
	  break;
	case 0xed:
	  printf ("%04x %02x %02x\t", addr, ReadRAM (addr),
		  ReadRAM (addr + 1));
	  ptr = &OpCodeList[(unsigned int) ReadRAM (addr + 1)];
	  printf ("%s\n", ptr->code5);
	  break;
	case 0xfd:
	  break;
	default:
	  switch (size)
	    {
	    case 1:
	      printf ("%04x %02x\t", addr, ReadRAM (addr));
	      printf ("\t\t%s\n", ptr->code1);
	      break;
	    case 2:
	      printf ("%04x %02x %02x\t", addr, ReadRAM (addr),
		      ReadRAM (addr + 1));
	      printf ("\t\t%s\t%02x\n", ptr->code1, ReadRAM (addr + 1));
	      break;
	    case 3:
	      printf ("%04x %02x %02x%02x\t", addr, ReadRAM (addr),
		      ReadRAM (addr + 1), ReadRAM (addr + 2));
	      printf ("%s\t%02x%02x\n", ptr->code1, ReadRAM (addr + 1),
		      ReadRAM (addr + 2));
	      break;
	    default:
	      printf ("%s\t%02x%02x%02x\n",
		      OpCodeList[ReadRAM (addr), level + 1].code1,
		      ReadRAM (addr + 1), ReadRAM (addr + 2),
		      ReadRAM (addr + 3));
	      break;
	    }
	  break;
	}
    }
}

/* print out all the registers */
void
DumpReg ()
{
#ifdef BREAK

  if (PCAddress == BreakAddr)
    printf ("Hit break point\n");

#endif
#ifdef STACKTRACE
  int i;
  if (SP <= 0xff00)
    return;
  printf ("\n%04x ", SP);
  for (i = SP; i <= 0xfffe; i++)
    {
      printf ("%02x ", ReadRAM (i));
    }
  printf ("\n");
#endif
  if (TraceReg)
    {
      printf ("%04x ", PC);
      printf ("%02x %02x %02x %02x %02x %02x %02x ", A, B, C,
	      D, E, H, L);
      printf ("%04x ", SP);
  //    printf ("     %02x %02x %02x %02x %02x %02x %02x ", A_, B_,
//	      C_, D_, E_, H_, L_);
 //     printf ("\n%04x %04x %02x %02x\n", IX, IY, I, IFF);

      if (F & S_FLAG)
	printf ("S ");
      if (F & Z_FLAG)
	printf ("Z ");
      if (F & H_FLAG)
	printf ("H ");
      if (F & P_FLAG)
	printf ("P ");
      if (F & N_FLAG)
	printf ("N ");
      if (F & C_FLAG)
	printf ("C ");

      printf ("\n");
    }

}
