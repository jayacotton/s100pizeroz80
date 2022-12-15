/* simulate a z80 cpu in this code */

#include <stdio.h>
#include "opcodes.h"

void main()
{
int i;
struct OpCodes *ptr;

	ptr = &OpCodeList[0];

	for(i=0;i<256;i++){
		printf("%02x %s\t%s\t%s\t%s\t%s\n",ptr->Val, ptr->code1, ptr->code2, ptr->code3,
				ptr->code4,ptr->code5);
		ptr++;
	}
}

