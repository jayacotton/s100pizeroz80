/* simulate a z80 cpu in this code */

#include <stdlib.h>
#include <stdio.h>
#include "z80sim.h"
#include <ctype.h>

extern void s100_init();
extern int TraceFlag;
extern int TraceReg;
extern void PrintInstruction();
extern void LoadBootRom();
extern void SnapShot();
extern void DumpReg();
extern int parity[];
extern void WriteRAM();
extern char ReadRAM();
extern void WritePort();
extern char ReadPort();

#define FETCHBYTE(a) {Low = ReadRAM(a++);}
#define FETCHADDR(a) {Low = ReadRAM(a++); High = ReadRAM(a++);}
#define TRACE(a,b,c) {PrintInstruction(a,b,c);}
#define DEC(a,b) {if(b==0x0) a--;b--;}
#define INC(a,b) {if(b==0xff)a++;b++;}


/* push pop code */

void Push(unsigned char hi, unsigned char low)
{
	WriteRAM(StackPointer-2,low);
	WriteRAM(StackPointer-1,hi);
    StackPointer -= 2;
}

void Pop(unsigned char *hi, unsigned char *low)
{
    *hi = ReadRAM(StackPointer + 1);
    *low = ReadRAM(StackPointer);
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
void Compair(unsigned char a, unsigned char b)
{
    if (a == b)
	CpuStatus |= ZFlag;
    else
	CpuStatus &= ~ZFlag;
/* need to figure out rest of flag bits */
}

#define BING() { printf("missing %x\n",Instruction);exit(0);}
void RunCode()
{
    unsigned char Instruction;
    unsigned char Low, High;
    unsigned short addr;

    while (1) {
	DumpReg();
	Instruction = ReadRAM(PCAddress++);	/* going to need to fix this */

	switch (Instruction) {
	case 0x0:
	    TRACE(PCAddress - 1, 1, 0);
	    break;
	case 0x1:		/* ld bc,# */
	    TRACE(PCAddress - 1, 3, 0);
	    FETCHADDR(PCAddress);
	    Breg = High;
	    Creg = Low;
	    break;
	case 0x2:
	    BING();
	    break;
	case 0x3:
	    BING();
	    break;
	case 0x4:
	    BING();
	    break;
	case 0x5:
	    BING();
	    break;
	case 0x6:		/* ld b,# */
	    TRACE(PCAddress - 1, 2, 0);
	    FETCHBYTE(PCAddress);
	    Breg = Low;
	    break;
	case 0x7:
	    BING();
	    break;
	case 0x8:
	    BING();
	    break;
	case 0x9:
	    BING();
	    break;
	case 0xA:
	    BING();
	    break;
	case 0xB:
	    TRACE(PCAddress - 1, 1, 0);
	    DEC(Breg, Creg);
	    break;
	case 0xC:
	    BING();
	    break;
	case 0xD:
		TRACE(PCAddress-1,1,0);
		Creg--;
		CpuStatus = (Creg)?(CpuStatus |= ZFlag):(CpuStatus &=~ZFlag);
		CpuStatus |= NFlag;
		CpuStatus = (parity[Creg])?(CpuStatus |= PFFlag):(CpuStatus &= ~PFFlag);
	    break;
	case 0xE:
	    TRACE(PCAddress - 1, 2, 0);
	    FETCHBYTE(PCAddress);
	    Creg = Low;
	    break;
	case 0xF:		/* rrca */
	    TRACE(PCAddress - 1, 1, 0);
	    Areg = Areg >> 1;
	    if (Areg & 1)
		CpuStatus |= CFlag;
	    else
		CpuStatus &= ~CFlag;
	    break;
	case 0x10:		/* djnz # */
	    TRACE(PCAddress - 1, 2, 0);
	    FETCHBYTE(PCAddress);
	    if (--Breg)
		PCAddress += (signed char) Low;

	    break;
	case 0x11:/* ld de,# */
		TRACE(PCAddress-1,3,0);
		FETCHADDR(PCAddress);
		Dreg = High;
		Lreg = Low;

	    break;
	case 0x12:
	    BING();
	    break;
	case 0x13:
	    BING();
	    break;
	case 0x14:
	    BING();
	    break;
	case 0x15:
	    BING();
	    break;
	case 0x16:
	    BING();
	    break;
	case 0x17:
	    BING();
	    break;
	case 0x18:		/* jump relative */
	    TRACE(PCAddress - 1, 2, 1);
	    FETCHBYTE(PCAddress);
	    PCAddress += (signed char) Low;
	    break;
	case 0x19:
	    BING();
	    break;
	case 0x1A:
	    BING();
	    break;
	case 0x1B:
	    BING();
	    break;
	case 0x1C:
	    BING();
	    break;
	case 0x1D:
	    BING();
	    break;
	case 0x1E:/* ld e,#*/
	    TRACE(PCAddress - 1, 1, 0);
		FETCHBYTE(PCAddress);
		Ereg = Low;

	    break;
	case 0x1F:		/* rra */
	    {
		unsigned char bit;
		TRACE(PCAddress - 1, 1, 0);
		bit = (CpuStatus & CFlag) ? 1 : 0;
		Areg = Areg >> 1;
		if (bit) {
		    Areg |= bit << 8;
		    CpuStatus |= CFlag;
		} else {
		    CpuStatus &= ~CFlag;
		}

	    }
	    break;
	case 0x20:		/* jr nz */
	    TRACE(PCAddress - 1, 2, 1);
	    FETCHBYTE(PCAddress);
	    if ((CpuStatus & ZFlag) == 0)
		PCAddress += (signed char) Low;
	    break;
	case 0x21:
	    TRACE(PCAddress - 1, 3, 1);
	    FETCHADDR(PCAddress);
	    Hreg = High;
	    Lreg = Low;
	    break;
	case 0x22:
	    BING();
	    break;
	case 0x23:
	    TRACE(PCAddress - 1, 1, 0);
	    INC(Hreg, Lreg);
	    break;
	case 0x24:
	    TRACE(PCAddress - 1, 1, 0);
	    Hreg += 1;
	    break;
	case 0x25:
	    TRACE(PCAddress - 1, 1, 0);
	    Hreg -= 1;
	    break;
	case 0x26:
	    BING();
	    break;
	case 0x27:		/* daa */
	    TRACE(PCAddress - 1, 1, 0);
/* *INDENT-OFF* */
{/* from udo monks z80pack z80code */
        int tmp_a = Areg;
        int low_nibble = Areg & 0x0f;
        int carry = (CpuStatus & CFlag);

        if (CpuStatus & NFlag) {               /* subtraction */
                int adjustment = (carry || (tmp_a > 0x99)) ? 0x160 : 0x00;

                if ((CpuStatus & HFlag) || (low_nibble > 9)) {
                        if (low_nibble > 5) {
                                CpuStatus &= ~HFlag;
                        }
                        tmp_a = (tmp_a - 6) & 0xff;
                }
                tmp_a -= adjustment;
        } else {                        /* addition */
                if ((low_nibble > 9) || (CpuStatus & HFlag)) {
                        (low_nibble > 9) ? (CpuStatus |= HFlag) : (CpuStatus &= ~HFlag);
                        tmp_a += 6;
                }
                if (((tmp_a & 0x1f0) > 0x90) || carry) {
                        tmp_a += 0x60;
                }
        }

        (carry || (tmp_a & 0x100)) ?  (CpuStatus |= CFlag) : (CpuStatus &= ~CFlag);
        Areg = (tmp_a & 0xff);
        (Areg) ? (CpuStatus &= ~ZFlag) : (CpuStatus |= ZFlag);
        (Areg & 128) ? (CpuStatus |= SFlag) : (CpuStatus &= ~SFlag);
        (parity[Areg]) ? (CpuStatus &= ~PFFlag) : (CpuStatus |= PFFlag);
}
/* *INDENT-ON* */
	    break;
	case 0x28:		/* jr z */
	    TRACE(PCAddress - 1, 2, 0);
	    FETCHBYTE(PCAddress);
	    if ((CpuStatus & ZFlag))
		PCAddress += (signed char) Low;

	    break;
	case 0x29:
	    BING();
	    break;
	case 0x2A:
	    BING();
	    break;
	case 0x2B:
	    BING();
	    break;
	case 0x2C:
	    BING();
	    break;
	case 0x2D:
	    BING();
	    break;
	case 0x2E:
	    BING();
	    break;
	case 0x2F:
	    TRACE(PCAddress - 1, 1, 1);
	    Areg = -Areg;
	    break;
	case 0x30:
	    BING();
	    break;
	case 0x31:
	    TRACE(PCAddress - 1, 3, 1);
	    FETCHADDR(PCAddress);
	    StackPointer = High << 8 | Low;
	    break;
	case 0x32: /* ld (addr),a */
		TRACE(PCAddress-1,3,0);
		FETCHADDR(PCAddress);
		WriteRAM(High<<8|Low,Areg);
	    break;
	case 0x33:
	    BING();
	    break;
	case 0x34:
	    BING();
	    break;
	case 0x35:
	    BING();
	    break;
	case 0x36:
	    BING();
	    break;
	case 0x37:
	    TRACE(PCAddress - 1, 1, 0);
	    CpuStatus |= CFlag;
	    break;
	case 0x38:
	    BING();
	    break;
	case 0x39:
	    BING();
	    break;
	case 0x3A:
	    TRACE(PCAddress - 1, 3, 0);
	    FETCHADDR(PCAddress);
	    Areg = ReadRAM(High << 8 | Low);
	    break;
	case 0x3B:
	    BING();
	    break;
	case 0x3C:
	    BING();
	    break;
	case 0x3D:
	    TRACE(PCAddress - 1, 1, 0);
	    Areg -= 1;
	    if (Areg == 0)
		CpuStatus = ZFlag;
	    else
		CpuStatus &= ~ZFlag;
	    break;
	case 0x3E:
	    TRACE(PCAddress - 1, 2, 0);	/* 2 byte instruction */
	    FETCHBYTE(PCAddress);
	    Areg = Low;
	    break;
	case 0x3F:
	    BING();
	    break;
	case 0x40:
	    BING();
	    break;
	case 0x41:
	    BING();
	    break;
	case 0x42:
	    BING();
	    break;
	case 0x43:
	    BING();
	    break;
	case 0x44:
	    BING();
	    break;
	case 0x45:
	    BING();
	    break;
	case 0x46:
	    BING();
	    break;
	case 0x47:
	    TRACE(PCAddress - 1, 1, 0);
	    Breg = Areg;
	    break;
	case 0x48:
	    BING();
	    break;
	case 0x49:
	    BING();
	    break;
	case 0x4A:
	    BING();
	    break;
	case 0x4B:
	    BING();
	    break;
	case 0x4C:
	    BING();
	    break;
	case 0x4D:
	    BING();
	    break;
	case 0x4E:
	    BING();
	    break;
	case 0x4F:
	    TRACE(PCAddress - 1, 1, 0);
	    Creg = Areg;
	    break;
	case 0x50:
	    BING();
	    break;
	case 0x51:
	    BING();
	    break;
	case 0x52:
	    BING();
	    break;
	case 0x53:
	    BING();
	    break;
	case 0x54:
	    BING();
	    break;
	case 0x55:
	    BING();
	    break;
	case 0x56:
	    BING();
	    break;
	case 0x57:
	    TRACE(PCAddress - 1, 1, 0);
	    Dreg = Areg;
	    break;
	case 0x58:
	    BING();
	    break;
	case 0x59:
	    BING();
	    break;
	case 0x5A:
	    BING();
	    break;
	case 0x5B:
	    BING();
	    break;
	case 0x5C:
	    BING();
	    break;
	case 0x5D:
	    BING();
	    break;
	case 0x5E:
	    BING();
	    break;
	case 0x5F:
	    TRACE(PCAddress - 1, 1, 0);
	    Ereg = Areg;
	    break;
	case 0x60:
	    BING();
	    break;
	case 0x61:
	    BING();
	    break;
	case 0x62:
	    BING();
	    break;
	case 0x63:
	    BING();
	    break;
	case 0x64:
	    BING();
	    break;
	case 0x65:
	    BING();
	    break;
	case 0x66:
		TRACE(PCAddress-1,1,0);
		addr = Hreg<<8|Lreg;
		Hreg = ReadRAM(addr);
	    break;
	case 0x67:
	    BING();
	    break;
	case 0x68:
	    BING();
	    break;
	case 0x69:
	    BING();
	    break;
	case 0x6A:
	    BING();
	    break;
	case 0x6B:
	    BING();
	    break;
	case 0x6C:
	    BING();
	    break;
	case 0x6D:
	    BING();
	    break;
	case 0x6E:
	    BING();
	    break;
	case 0x6F:
		TRACE(PCAddress-1,1,0);
		Lreg = Areg;
	    break;
	case 0x70:
	    BING();
	    break;
	case 0x71:
	    BING();
	    break;
	case 0x72:
	    BING();
	    break;
	case 0x73:
	    BING();
	    break;
	case 0x74:
	    BING();
	    break;
	case 0x75:
	    BING();
	    break;
	case 0x76:
	    BING();
	    break;
	case 0x77:
	    TRACE(PCAddress - 1, 1, 0);
	    addr = Hreg << 8 | Lreg;
	    WriteRAM(addr, Areg);
	    break;
	case 0x78:
	    TRACE(PCAddress - 1, 1, 0);
	    Areg = Breg;
	    break;
	case 0x79:
	    TRACE(PCAddress - 1, 1, 0);
	    Areg = Creg;
	    break;
	case 0x7A:
	    TRACE(PCAddress - 1, 1, 0);
	    Areg = Dreg;
	    break;
	case 0x7B:
	    TRACE(PCAddress - 1, 1, 0);
	    Areg = Ereg;
	    break;
	case 0x7C:
	    TRACE(PCAddress - 1, 1, 0);
	    Areg = Hreg;
	    break;
	case 0x7D:
	    TRACE(PCAddress - 1, 1, 0);
	    Areg = Lreg;
	    break;
	case 0x7E:
	    TRACE(PCAddress - 1, 1, 0);
	    addr = Hreg << 8 | Lreg;
	    Areg = ReadRAM(addr);
	    break;
	case 0x7F:
	    BING();
	    break;
	case 0x80:
	    BING();
	    break;
	case 0x81:
	    BING();
	    break;
	case 0x82:
	    BING();
	    break;
	case 0x83:
	    BING();
	    break;
	case 0x84:
	    BING();
	    break;
	case 0x85:
		TRACE(PCAddress-1,1,0);
		Areg += Lreg;
		CpuStatus = (Areg)?(0):(ZFlag);
		CpuStatus |= (Areg&0x80)?(CFlag):0;
	    break;
	case 0x86:
	    BING();
	    break;
	case 0x87: /* add a,a */
		TRACE(PCAddress-1,1,0);
		Areg += Areg;
		CpuStatus = (Areg)?(0):(ZFlag);
		CpuStatus |= (Areg&0x80)?(CFlag):0;
	    break;
	case 0x88:
	    BING();
	    break;
	case 0x89:
	    BING();
	    break;
	case 0x8A:
	    BING();
	    break;
	case 0x8B:
	    BING();
	    break;
	case 0x8C:
	    BING();
	    break;
	case 0x8D:
	    BING();
	    break;
	case 0x8E:
	    BING();
	    break;
	case 0x8F:
	    TRACE(PCAddress - 1, 1, 1);
	    Areg += (Areg + ((CpuStatus & CFlag) ? 1 : 0));
		CpuStatus = (Areg)?(0):(ZFlag);
		CpuStatus |= (Areg&0x80)?(CFlag):0;
	
	    break;
	case 0x90:
	    BING();
	    break;
	case 0x91:
	    BING();
	    break;
	case 0x92:
	    BING();
	    break;
	case 0x93:
	    BING();
	    break;
	case 0x94:
	    BING();
	    break;
	case 0x95:
	    BING();
	    break;
	case 0x96:
	    BING();
	    break;
	case 0x97:
	    BING();
	    break;
	case 0x98:
	    BING();
	    break;
	case 0x99:
	    BING();
	    break;
	case 0x9A:
	    BING();
	    break;
	case 0x9B:
	    BING();
	    break;
	case 0x9C:
	    BING();
	    break;
	case 0x9D:
	    BING();
	    break;
	case 0x9E:
	    BING();
	    break;
	case 0x9F:
	    BING();
	    break;
	case 0xA0:
	    BING();
	    break;
	case 0xA1:
	    BING();
	    break;
	case 0xA2:
	    BING();
	    break;
	case 0xA3:
	    BING();
	    break;
	case 0xA4:
	    BING();
	    break;
	case 0xA5:
	    BING();
	    break;
	case 0xA6:
	    BING();
	    break;
	case 0xA7:
	    BING();
	    break;
	case 0xA8:
	    BING();
	    break;
	case 0xA9:
	    BING();
	    break;
	case 0xAA:
	    BING();
	    break;
	case 0xAB:
	    BING();
	    break;
	case 0xAC:
	    BING();
	    break;
	case 0xAD:
	    BING();
	    break;
	case 0xAE:
	    BING();
	    break;
	case 0xAF:
	    TRACE(PCAddress - 1, 1, 0);
	    Areg ^= Areg;
	    CpuStatus = ZFlag;
	    break;
	case 0xB0:
	    TRACE(PCAddress - 1, 1, 0);
	    Areg |= Breg;
		CpuStatus = (Areg)?0:ZFlag;
	    break;
	case 0xB1:
	    BING();
	    break;
	case 0xB2:
	    BING();
	    break;
	case 0xB3:
	    BING();
	    break;
	case 0xB4:
	    BING();
	    break;
	case 0xB5:
	    BING();
	    break;
	case 0xB6:
	    BING();
	    break;
	case 0xB7:
		TRACE(PCAddress-1,1,0);
		Areg |= Areg;
		CpuStatus = 0;
	    break;
	case 0xB8:
	    BING();
	    break;
	case 0xB9:
	    BING();
	    break;
	case 0xBA:
	    BING();
	    break;
	case 0xBB:
	    BING();
	    break;
	case 0xBC:
	    BING();
	    break;
	case 0xBD:
	    BING();
	    break;
	case 0xBE:
	    TRACE(PCAddress - 1, 1, 0);
	    addr = Hreg << 8 | Lreg;
	    Compair(Areg, ReadRAM(addr));
	    break;
	case 0xBF:
	    BING();
	    break;
	case 0xC0:
	    BING();
	    break;
	case 0xC1:		/* pop bc */
	    TRACE(PCAddress - 1, 1, 0);
	    Pop(&Breg, &Creg);
	    break;
	case 0xC2:
	    TRACE(PCAddress - 1, 3, 0);
	    FETCHADDR(PCAddress);
	    PCAddress =
		(CpuStatus & ZFlag) ? (High << 8 | Low) : PCAddress;
	    break;
	case 0xC3:		/* jump */
	    TRACE(PCAddress - 1, 3, 0);	/* 3 byte instruction */
	    FETCHADDR(PCAddress);
	    PCAddress = High << 8 | Low;
	    break;
	case 0xC4:
	    TRACE(PCAddress - 1, 3, 0);
	    FETCHADDR(PCAddress);
	    Push(PCAddress >> 8, PCAddress & 0xff);
	    if (!(CpuStatus & ZFlag))
		PCAddress = High << 8 | Low;
	    break;
	case 0xC5:
	    TRACE(PCAddress - 1, 1, 0);
	    Push(Breg, Creg);
	    break;
	case 0xC6:
	    TRACE(PCAddress - 1, 2, 0);
	    FETCHBYTE(PCAddress);
	    Areg += Low;
	    CpuStatus = (Areg & 0x80) ? (CpuStatus |=
					 CFlag) : (CpuStatus &= ~CFlag);
	    CpuStatus = (Areg) ? (CpuStatus |= ZFlag) : (CpuStatus &=
							 ~ZFlag);
	    CpuStatus &= ~NFlag;
	    break;
	case 0xC7:
	    BING();
	    break;
	case 0xC8:		/* ret z */
	    TRACE(PCAddress - 1, 1, 0);
	    if (CpuStatus & ZFlag) {
		Pop(&High, &Low);
		PCAddress = High << 8 | Low;
	    }
	    break;
	case 0xC9:	/* ret */
	    TRACE(PCAddress - 1, 1, 0);
	    Pop(&High, &Low);
	    PCAddress = High << 8 | Low;
	    break;
	case 0xCA: /* jp z,#*/
	    TRACE(PCAddress - 1, 3, 0);
	    FETCHADDR(PCAddress);
	    addr = High << 8 | Low;
	    if (CpuStatus & ZFlag)
		PCAddress = addr;
	    break;
	case 0xCB:
	    TRACE(PCAddress - 1, 2, 1);
	    FETCHBYTE(PCAddress);
	    switch (Low) {
	    case 0x6f:		/* bit 5,a */
		if (Areg & 0x10)
		    CpuStatus |= ZFlag;
		else
		    CpuStatus &= ~ZFlag;
		break;
	    case 0x23:		/* sla e */
		Ereg <<= 1;
		CpuStatus = (Ereg & 0x80) ? CFlag : 0;
		CpuStatus |= (Ereg)?(0):(ZFlag);
		break;
	    default:
		printf("Did not catch a CB opcode  %x\n", Low);
		break;
	    }
	    break;
	case 0xCC:
	    BING();
	    break;
	case 0xCD:		/* call */
	    TRACE(PCAddress - 1, 3, 0);
	    FETCHADDR(PCAddress);
	    Push(PCAddress >> 8, PCAddress & 0xff);
	    PCAddress = (High & 0xff) << 8 | Low & 0xff;
	    break;
	case 0xCE:		/* adc a,# */
	    TRACE(PCAddress - 1, 2, 1);
	    FETCHBYTE(PCAddress);
	    Areg += (Low + ((CpuStatus & CFlag) ? 1 : 0));
		CpuStatus = (Areg)?0:ZFlag;
		CpuStatus |= (Areg & 0x80)? CFlag : 0;
		
	    break;
	case 0xCF:
	    BING();
	    break;
	case 0xD0: /* ret nc */
		TRACE(PCAddress-1,1,0);
		if(!(CpuStatus & CFlag)){
			Pop(&High,&Low);
			PCAddress = High << 8| Low;
		}
	    break;
	case 0xD1: /* pop de */
	    TRACE(PCAddress - 1, 1, 0);
	    Pop(&Dreg, &Ereg);
	    break;
	case 0xD2:		/* jmp nc,addr */
	    TRACE(PCAddress - 1, 3, 0);
	    FETCHADDR(PCAddress);
	    if (!(CpuStatus & CFlag))
		PCAddress = High << 8 | Low;
	    break;
	case 0xD3:		/* special case i/o instruction */
	    TRACE(PCAddress - 1, 2, 0);	/* 2 byte instruction */
	    FETCHBYTE(PCAddress);
	    WritePort(Low, Areg);
	    break;
	case 0xD4:
	    BING();
	    break;
	case 0xD5:
	    TRACE(PCAddress - 1, 1, 0);
	    Push(Dreg, Ereg);
	    break;
	case 0xD6:
		TRACE(PCAddress -1,2,0);
		FETCHBYTE(PCAddress);
		High = 0;
		if(Areg < Low) High = 1;
		Areg -= Low;
		CpuStatus = (Areg)?0:ZFlag;
		CpuStatus |= High?CFlag:0;
		
	    break;
	case 0xD7:
	    BING();
	    break;
	case 0xD8: /* ret c */
		TRACE(PCAddress-1,1,0);
		if(CpuStatus & CFlag)
		{
			Pop (&High,&Low);
			PCAddress = High<<8|Low;
		}
	    break;
	case 0xD9:
	    BING();
	    break;
	case 0xDA:
	    TRACE(PCAddress - 1, 3, 0);
	    FETCHADDR(PCAddress);
	    if (CpuStatus & CFlag)
		PCAddress = High << 8 | Low;
	    break;
	case 0xDB:
	    TRACE(PCAddress - 1, 2, 0);
	    FETCHBYTE(PCAddress);
	    Areg = ReadPort(Low);
	    break;
	case 0xDC:
	    BING();
	    break;
	case 0xDD:
	    TRACE(PCAddress - 1, 2, 5);
	    FETCHBYTE(PCAddress);
	    switch (Low) {
	    case 0xE1:	/*  pop ix */
		Pop(&High, &Low);
		IXreg = High << 8 | Low;
		break;
	    case 0xE5:		/* push ix */
		Push(IXreg >> 8, IXreg & 0xff);
		break;
	    default:
		printf("*** DD did not catch the operand \n");
		break;
	    }
	    break;
	case 0xDE:
	    BING();
	    break;
	case 0xDF:
	    BING();
	    break;
	case 0xE0:
	    BING();
	    break;
	case 0xE1:  /* pop hl */
	    TRACE(PCAddress - 1, 1, 0);
	    Pop(&Hreg, &Lreg);
	    break;
	case 0xE2:
	    BING();
	    break;
	case 0xE3:
	    BING();
	    break;
	case 0xE4:
	    BING();
	    break;
	case 0xE5:
	    TRACE(PCAddress - 1, 1, 0);
	    Push(Hreg, Lreg);
	    break;
	case 0xE6:
	    TRACE(PCAddress - 1, 2, 0);
	    FETCHBYTE(PCAddress);
	    Areg &= Low;
	    CpuStatus = (Areg)?(0):(ZFlag); 
	    break;
	case 0xE7:
	    BING();
	    break;
	case 0xE8:
	    BING();
	    break;
	case 0xE9: /* jp (hl) */
	TRACE(PCAddress-1,1,0);
		PCAddress = Hreg<<8 | Lreg;	
	    break;
	case 0xEA:
	    BING();
	    break;
	case 0xEB:
	    BING();
	    break;
	case 0xEC:
	    BING();
	    break;
	case 0xED:
	    TRACE(PCAddress - 1, 2, 5);
	    FETCHBYTE(PCAddress);
	    switch (Low) {
	    case 0x47:
		Ireg = Areg;
		break;
	    case 0x52:
		BING();
		break;
	    case 0x78:
		TRACE(PCAddress - 1, 1, 0);
		Areg = Breg;
		break;
	    case 0x59:
		BING();
		break;
	    case 0xB3:		/* otir */
		/* c = address */
		/* b = byte count */
		/* HL = input pointer */
		addr = Hreg << 8 | Lreg;
		do {
		    unsigned char l;
		    l = ReadRAM(addr++);
		    WritePort(Breg << 8 | Creg, l);
		} while (--Breg);
		Hreg = addr >> 8;
		Lreg = addr & 0xff;
		break;
	    case 0xB2:
		BING();
		break;
	    case 0x5B:
		BING();
		break;


	    default:
		printf("*** ED did not catch the operand \n");
		break;
	    }
	    break;
	case 0xEE:
		TRACE(PCAddress-1,2,0);
		FETCHBYTE(PCAddress);
		Areg ^= Low;
		CpuStatus = (Areg)?(ZFlag):0;
	    break;
	case 0xEF:
	    BING();
	    break;
	case 0xF0:
	    BING();
	    break;
	case 0xF1:  /* pop af */
	    TRACE(PCAddress - 1, 1, 1);
	    Pop(&Areg, &CpuStatus);
	    break;
	case 0xF2:
	    BING();
	    break;
	case 0xF3:
	    TRACE(PCAddress - 1, 1, 0);
	    IntState = 0;
	    break;
	case 0xF4:
	    BING();
	    break;
	case 0xF5:
	    TRACE(PCAddress - 1, 1, 0);
	    Push(Areg, CpuStatus);
	    break;
	case 0xF6:
		TRACE(PCAddress -1,2,0);
		FETCHBYTE(PCAddress);
		Areg |= Low;
		CpuStatus = (Areg)?(ZFlag):(0);
	    break;
	case 0xF7:
	    BING();
	    break;
	case 0xF8:/* ret m */
		TRACE(PCAddress-1,1,0);
		if(CpuStatus & SFlag){
			Pop (&High,&Low);
			PCAddress = High<<8|Low;
		}
	    break;
	case 0xF9:
	    TRACE(PCAddress - 1, 1, 0);
	    StackPointer = Hreg << 8 | Lreg;
	    break;
	case 0xFA:
	    BING();
	    break;
	case 0xFB:
	    BING();
	    break;
	case 0xFC:
	    BING();
	    break;
	case 0xFD:
	    BING();
	    break;
	case 0xFE:
	    TRACE(PCAddress - 1, 2, 0);
	    FETCHBYTE(PCAddress);
	    Compair(Areg, Low);
	    break;
	case 0xFF:
	    BING();
	    break;

	}
    }
}

void main(int argc, char *argv[])
{
    int i;
    unsigned char h, l;

/* initialize the s100 bus hardware */
	s100_init();
//	Send_Z80Reset();
/* load the boot prom code into ReadRAM at 0xe000 and start it.
of course, on the real hardware we will just start running at 0xe000 since
the boot prom is located in our address space. */
	LoadBootRom();
    PCAddress = 0xe000;
//TraceFlag = 1;
//TraceReg = 1;
    RunCode();
}
