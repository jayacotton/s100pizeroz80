/* utility code for the z80 simulator */

/* all the stuff that we need for running debug on a LINUX system
without the hardware connected */

#include <stdio.h>
#include <stdlib.h>
#include "z80sim.h"

int TraceFlag;
extern OPCODES OpCodeList[];

#ifdef LINUX

extern unsigned char ram[];
FILE *in;

void LoadBootRom()
{
    unsigned char *loadpoint;
    printf("read and load the boot rom code\n");
    loadpoint = &ram[0x100];
    in = fopen("MASTER0.COM", "r");
    if (in == 0) {
	printf("can open boot rom\n");
	exit(0);
    }
    fread(loadpoint, 1, 61000, in);
    fclose(in);
}
#else
#endif

/* all the utility code that will work without the s100 h/w connected */

/* trace instruction at address */

void PrintInstruction(unsigned short addr, int size, int level)
{
    struct OpCodes *ptr;

/* address is the current address of PCAddress */
/* size is the number of bytes to print for this instruction */
/* level is the depth index for the instruction decode */


    if (TraceFlag) {
	ptr = &OpCodeList[(unsigned int) ram[addr]];
/* deal with special case instructions */
	switch (ram[addr]) {
	case 0xcb:
	    break;
	case 0xdd:
	    break;
	case 0xed:
	    printf("%04x %02x %02x\t", addr, ram[addr], ram[addr + 1]);
	    ptr = &OpCodeList[(unsigned int) ram[addr + 1]];
	    printf("%s\n", ptr->code5);
	    break;
	case 0xfd:
	    break;
	default:
	    switch (size) {
	    case 1:
		printf("%04x %02x\t", addr, ram[addr]);
		printf("%s\n", ptr->code1);
		break;
	    case 2:
		printf("%04x %02x %02x\t", addr, ram[addr], ram[addr + 1]);
		printf("%s\t%02x\n", ptr->code1, ram[addr + 1]);
		break;
	    case 3:
		printf("%04x %02x %02x%02x\t", addr, ram[addr],
		       ram[addr + 1], ram[addr + 2]);
		printf("%s\t%02x%02x\n", ptr->code1, ram[addr + 1],
		       ram[addr + 2]);
		break;
	    default:
		printf("%s\t%02x%02x%02x\n",
		       OpCodeList[ram[addr], level + 1].code1,
		       ram[addr + 1], ram[addr + 2], ram[addr + 3]);
		break;
	    }
	    break;
	}
    }
}
