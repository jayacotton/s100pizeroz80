/* debug code */
#include <stdio.h>

#include "opcodes.h"
extern unsigned char ram[];
void DumpOpCodes()
{
    int i;
    struct OpCodes *ptr;

    ptr = &OpCodeList[0];

    for (i = 0; i < 256; i++) {
	printf("%02x %s\t%s\t%s\t%s\t%s\n", ptr->Val, ptr->code1,
	       ptr->code2, ptr->code3, ptr->code4, ptr->code5);
	ptr++;
    }
}

void SnapShot(unsigned int addr, int size)
{
    int Count, Line;

    for (Count = 0, Line = 0; Count < size; Count++, Line++) {
	if (Line == 0)
	    printf("0x%04x ", (unsigned short) addr);
	if (Line == 16) {
	    Line = 0;
	    printf("\n0x%04x ", (unsigned short) addr);
	}
	printf("0x%02x ", ram[addr++]);
    }
    printf("\n");
}
