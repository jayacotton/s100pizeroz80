/*  copied from 
          Full Z80 Opcode List Including Undocumented Opcodes
          ===================================================
               File: DOCS.Comp.Z80.OpList - Update: 0.10
                Author: J.G.Harston - Date: 09-09-1997
   */

/* stock, DD nn,CD nn,FD CB FF nn,ED nn  */ 
{0x00 ,"NOP","-","RLC  B","rlc (iy+0)->b","MOS_QUIT"},
{0x01 ,"LD   BC,&0000","-","RLC  C","rlc (iy+0)->c","MOS_CLI"},
{0x02 ,"LD   (BC),A","-","RLC  D","rlc (iy+0)->d","MOS_BYTE"},
{0x03 ,"INC  BC","-","RLC  E","rlc (iy+0)->e","MOS_WORD"},
{0x04 ,"INC  B","-","RLC  H","rlc (iy+0)->h","MOS_WRCH"},
{0x05 ,"DEC  B","-","RLC  L","rlc (iy+0)->l","MOS_RDCH"},
{0x06 ,"LD   B,&00","-","RLC  (HL)","RLC  (IY+0)","MOS_FILE"},
{0x07 ,"RLCA","-","RLC  A","rlc (iy+0)->a","MOS_ARGS"},
{0x08 ,"EX   AF,AF'","-","RRC  B","rrc (iy+0)->b","MOS_BGET"},
{0x09 ,"ADD  HL,BC","ADD  IX,BC","RRC  C","rrc (iy+0)->c","MOS_BPUT"},
{0x0A ,"LD   A,(BC)","-","RRC  D","rrc (iy+0)->d","MOS_GBPB"},
{0x0B ,"DEC  BC","-"," RRC  E","rrc (iy+0)->e","MOS_FIND"},
{0x0C ,"INC  C","-"," RRC  H","rrc (iy+0)->h","MOS_FF0C"},
{0x0D ,"DEC  C","-"," RRC  L","rrc (iy+0)->l","MOS_FF0D"},
{0x0E ,"LD   C,&00","-"," RRC  (HL)","RRC  (IY+0)","MOS_FF0E"},
{0x0F ,"RRCA","-"," RRC  A","rrc (iy+0)->a","MOS_FF0F"},
{0x10 ,"DJNZ &4546","-"," RL   B","rl  (iy+0)->b","-"},
{0x11 ,"LD   DE,&0000","-"," RL   C","rl  (iy+0)->c","-"},
{0x12 ,"LD   (DE),A","-"," RL   D","rl  (iy+0)->d","-"},
{0x13 ,"INC  DE","-"," RL   E","rl  (iy+0)->e","-"},
{0x14 ,"INC  D","-"," RL   H","rl  (iy+0)->h","-"},
{0x15 ,"DEC  D","-"," RL   L","rl  (iy+0)->l","-"},
{0x16 ,"LD   D,&00","-"," RL   (HL)","RL   (IY+0)","-"},
{0x17 ,"RLA","-"," RL   A","rl  (iy+0)->a","-"},
{0x18 ,"JR   &4546","-"," RR   B","rr  (iy+0)->b","-"},
{0x19 ,"ADD  HL,DE"," ADD  IX,DE"," RR   C","rr  (iy+0)->c","-"},
{0x1A ,"LD   A,(DE)","-"," RR   D","rr  (iy+0)->d","-"},
{0x1B ,"DEC  DE","-"," RR   E","rr  (iy+0)->e","-"},
{0x1C ,"INC  E","-"," RR   H","rr  (iy+0)->h","-"},
{0x1D ,"DEC  E","-"," RR   L","rr  (iy+0)->l","-"},
{0x1E ,"LD   E,&00","-"," RR   (HL)","RR   (IY+0)","-"},
{0x1F ,"RRA","-"," RR   A","rr  (iy+0)->a","-"},
{0x20 ,"JR   NZ,&4546","-"," SLA  B","sla (iy+0)->b","-"},
{0x21 ,"LD   HL,&0000"," LD   IX,&0000"," SLA  C","sla (iy+0)->c","-"},
{0x22 ,"LD  (&0000),HL"," LD  (&0000),IX"," SLA  D","sla (iy+0)->d","-"},
{0x23 ,"INC  HL"," INC  IX"," SLA  E","sla (iy+0)->e","-"},
{0x24 ,"INC  H"," INC  IXH"," SLA  H","sla (iy+0)->h","-"},
{0x25 ,"DEC  H"," DEC  IXH"," SLA  L","sla (iy+0)->l","-"},
{0x26 ,"LD   H,&00"," LD   IXH,&00"," SLA  (HL)","SLA  (IY+0)","-"},
{0x27 ,"DAA","-"," SLA  A","sla (iy+0)->a","-"},
{0x28 ,"JR   Z,&4546","-"," SRA  B","sra (iy+0)->b","-"},
{0x29 ,"ADD  HL,HL"," ADD  IX,IX"," SRA  C","sra (iy+0)->c","-"},
{0x2A ,"LD  HL,(&0000)"," LD  IX,(&0000)"," SRA  D","sra (iy+0)->d","-"},
{0x2B ,"DEC  HL"," DEC  IX"," SRA  E","sra (iy+0)->e","-"},
{0x2C ,"INC  L"," INC  IXL"," SRA  H","sra (iy+0)->h","-"},
{0x2D ,"DEC  L"," DEC  IXL"," SRA  L","sra (iy+0)->l","-"},
{0x2E ,"LD   L,&00"," LD   IXL,&00"," SRA  (HL)","SRA  (IY+0)","-"},
{0x2F ,"CPL","-"," SRA  A","sra (iy+0)->a","-"},
{0x30 ,"JR   NC,&4546","-"," SLS  B","sls (iy+0)->b","-"},
{0x31 ,"LD   SP,&0000","-"," SLS  C","sls (iy+0)->c","-"},
{0x32 ,"LD   (&0000),A","-"," SLS  D","sls (iy+0)->d","-"},
{0x33 ,"INC  SP","-"," SLS  E","sls (iy+0)->e","-"},
{0x34 ,"INC  (HL)"," INC  (IX+0)"," SLS  H","sls (iy+0)->h","-"},
{0x35 ,"DEC  (HL)"," DEC  (IX+0)"," SLS  L","sls (iy+0)->l","-"},
{0x36 ,"LD   (HL),&00"," LD  (IX+0),&00"," SLS  (HL)","SLS  (IY+0)","-"},
{0x37 ,"SCF","-"," SLS  A","sls (iy+0)->a","-"},
{0x38 ,"JR   C,&4546","-"," SRL  B","srl (iy+0)->b","-"},
{0x39 ,"ADD  HL,SP"," ADD  IX,SP"," SRL  C","srl (iy+0)->c","-"},
{0x3A ,"LD   A,(&0000)","-"," SRL  D","srl (iy+0)->d","-"},
{0x3B ,"DEC  SP","-"," SRL  E","srl (iy+0)->e","-"},
{0x3C ,"INC  A","-"," SRL  H","srl (iy+0)->h","-"},
{0x3D ,"DEC  A","-"," SRL  L","srl (iy+0)->l","-"},
{0x3E ,"LD   A,&00","-"," SRL  (HL)","SRL  (IY+0)","-"},
{0x3F ,"CCF","-"," SRL  A","srl (iy+0)->a","-"},
{0x40 ,"LD   B,B","-"," BIT  0,B","bit 0,(iy+0)->b","IN   B,(C)"},
{0x41 ,"LD   B,C","-"," BIT  0,C","bit 0,(iy+0)->c","OUT  (C),B"},
{0x42 ,"LD   B,D","-"," BIT  0,D","bit 0,(iy+0)->d","SBC  HL,BC"},
{0x43 ,"LD   B,E","-"," BIT  0,E","bit 0,(iy+0)->e","LD   (&0000),BC"},
{0x44 ,"LD   B,H"," LD   B,IXH"," BIT  0,H","bit 0,(iy+0)->h","NEG"},
{0x45 ,"LD   B,L"," LD   B,IXL"," BIT  0,L","bit 0,(iy+0)->l","RETN"},
{0x46 ,"LD   B,(HL)"," LD   B,(IX+0)"," BIT  0,(HL)","BIT  0,(IY+0)","IM   0"},
{0x47 ,"LD   B,A","-"," BIT  0,A","bit 0,(iy+0)->a","LD   I,A"},
{0x48 ,"LD   C,B","-"," BIT  1,B","bit 1,(iy+0)->b","IN   C,(C)"},
{0x49 ,"LD   C,C","-"," BIT  1,C","bit 1,(iy+0)->c","OUT  (C),C"},
{0x4A ,"LD   C,D","-"," BIT  1,D","bit 1,(iy+0)->d","ADC  HL,BC"},
{0x4B ,"LD   C,E","-"," BIT  1,E","bit 1,(iy+0)->e","LD   BC,(&0000)"},
{0x4C ,"LD   C,H"," LD   C,IXH"," BIT  1,H","bit 1,(iy+0)->h","[neg]"},
{0x4D ,"LD   C,L"," LD   C,IXL"," BIT  1,L","bit 1,(iy+0)->l","RETI"},
{0x4E ,"LD   C,(HL)"," LD   C,(IX+0)"," BIT  1,(HL)","BIT  1,(IY+0)","[im0]"},
{0x4F ,"LD   C,A","-"," BIT  1,A","bit 1,(iy+0)->a","LD   R,A"},
{0x50 ,"LD   D,B","-"," BIT  2,B","bit 2,(iy+0)->b","IN   D,(C)"},
{0x51 ,"LD   D,C","-"," BIT  2,C","bit 2,(iy+0)->c","OUT  (C),D"},
{0x52 ,"LD   D,D","-"," BIT  2,D","bit 2,(iy+0)->d","SBC  HL,DE"},
{0x53 ,"LD   D,E","-"," BIT  2,E","bit 2,(iy+0)->e","LD   (&0000),DE"},
{0x54 ,"LD   D,H"," LD   D,IXH"," BIT  2,H","bit 2,(iy+0)->h","[neg]"},
{0x55 ,"LD   D,L"," LD   D,IXL"," BIT  2,L","bit 2,(iy+0)->l","[retn]"},
{0x56 ,"LD   D,(HL)"," LD   D,(IX+0)"," BIT  2,(HL)","BIT  2,(IY+0)","IM   1"},
{0x57 ,"LD   D,A","-"," BIT  2,A","bit 2,(iy+0)->a","LD   A,I"},
{0x58 ,"LD   E,B","-"," BIT  3,B","bit 3,(iy+0)->b","IN   E,(C)"},
{0x59 ,"LD   E,C","-"," BIT  3,C","bit 3,(iy+0)->c","OUT  (C),E"},
{0x5A ,"LD   E,D","-"," BIT  3,D","bit 3,(iy+0)->d","ADC  HL,DE"},
{0x5B ,"LD   E,E","-"," BIT  3,E","bit 3,(iy+0)->e","LD   DE,(&0000)"},
{0x5C ,"LD   E,H"," LD   E,IXH"," BIT  3,H","bit 3,(iy+0)->h","[neg]"},
{0x5D ,"LD   E,L"," LD   E,IXL"," BIT  3,L","bit 3,(iy+0)->l","[reti]"},
{0x5E ,"LD   E,(HL)"," LD   E,(IX+0)"," BIT  3,(HL)","BIT  3,(IY+0)","IM   2"},
{0x5F ,"LD   E,A","-"," BIT  3,A","bit 3,(iy+0)->a","LD   A,R"},
{0x60 ,"LD   H,B"," LD   IXH,B"," BIT  4,B","bit 4,(iy+0)->b","IN   H,(C)"},
{0x61 ,"LD   H,C"," LD   IXH,C"," BIT  4,C","bit 4,(iy+0)->c","OUT  (C),H"},
{0x62 ,"LD   H,D"," LD   IXH,D"," BIT  4,D","bit 4,(iy+0)->d","SBC  HL,HL"},
{0x63 ,"LD   H,E"," LD   IXH,E"," BIT  4,E","bit 4,(iy+0)->e","LD   (&0000),HL"},
{0x64 ,"LD   H,H"," LD   IXH,IXH"," BIT  4,H","bit 4,(iy+0)->h","[neg]"},
{0x65 ,"LD   H,L"," LD   IXH,IXL"," BIT  4,L","bit 4,(iy+0)->l","[retn]"},
{0x66 ,"LD   H,(HL)"," LD   H,(IX+0)"," BIT  4,(HL)","BIT  4,(IY+0)","[im0]"},
{0x67 ,"LD   H,A"," LD   IXH,A"," BIT  4,A","bit 4,(iy+0)->a","RRD"},
{0x68 ,"LD   L,B"," LD   IXL,B"," BIT  5,B","bit 5,(iy+0)->b","IN   L,(C)"},
{0x69 ,"LD   L,C"," LD   IXL,C"," BIT  5,C","bit 5,(iy+0)->c","OUT  (C),L"},
{0x6A ,"LD   L,D"," LD   IXL,D"," BIT  5,D","bit 5,(iy+0)->d","ADC  HL,HL"},
{0x6B ,"LD   L,E"," LD   IXL,E"," BIT  5,E","bit 5,(iy+0)->e","LD   HL,(&0000)"},
{0x6C ,"LD   L,H"," LD   IXL,IXH"," BIT  5,H","bit 5,(iy+0)->h","[neg]"},
{0x6D ,"LD   L,L"," LD   IXL,IXL"," BIT  5,L","bit 5,(iy+0)->l","[reti]"},
{0x6E ,"LD   L,(HL)"," LD   L,(IX+0)"," BIT  5,(HL)","BIT  5,(IY+0)","[im0]"},
{0x6F ,"LD   L,A"," LD   IXL,A"," BIT  5,A","bit 5,(iy+0)->a","RLD"},
{0x70 ,"LD   (HL),B"," LD   (IX+0),B"," BIT  6,B","bit 6,(iy+0)->b","IN   F,(C)"},
{0x71 ,"LD   (HL),C"," LD   (IX+0),C"," BIT  6,C","bit 6,(iy+0)->c","OUT  (C),F"},
{0x72 ,"LD   (HL),D"," LD   (IX+0),D"," BIT  6,D","bit 6,(iy+0)->d","SBC  HL,SP"},
{0x73 ,"LD   (HL),E"," LD   (IX+0),E"," BIT  6,E","bit 6,(iy+0)->e","LD   (&0000),SP"},
{0x74 ,"LD   (HL),H"," LD   (IX+0),H"," BIT  6,H","bit 6,(iy+0)->h","[neg]"},
{0x75 ,"LD   (HL),L"," LD   (IX+0),L"," BIT  6,L","bit 6,(iy+0)->l","[retn]"},
{0x76 ,"HALT","-"," BIT  6,(HL)","BIT  6,(IY+0)","[im1]"},
{0x77 ,"LD   (HL),A"," LD   (IX+0),A"," BIT  6,A","bit 6,(iy+0)->a","[ld i,i?]"},
{0x78 ,"LD   A,B","-"," BIT  7,B","bit 7,(iy+0)->b","IN   A,(C)"},
{0x79 ,"LD   A,C","-"," BIT  7,C","bit 7,(iy+0)->c","OUT  (C),A"},
{0x7A ,"LD   A,D","-"," BIT  7,D","bit 7,(iy+0)->d","ADC  HL,SP"},
{0x7B ,"LD   A,E","-"," BIT  7,E","bit 7,(iy+0)->e","LD   SP,(&0000)"},
{0x7C ,"LD   A,H"," LD   A,IXH"," BIT  7,H","bit 7,(iy+0)->h","[neg]"},
{0x7D ,"LD   A,L"," LD   A,IXL"," BIT  7,L","bit 7,(iy+0)->l","[reti]"},
{0x7E ,"LD   A,(HL)"," LD   A,(IX+0)"," BIT  7,(HL)","BIT  7,(IY+0)","[im2]"},
{0x7F ,"LD   A,A","-"," BIT  7,A","bit 7,(iy+0)->a","[ld r,r?]"},
{0x80 ,"ADD  A,B","-"," RES  0,B","res 0,(iy+0)->b","-"},
{0x81 ,"ADD  A,C","-"," RES  0,C","res 0,(iy+0)->c","-"},
{0x82 ,"ADD  A,D","-"," RES  0,D","res 0,(iy+0)->d","-"},
{0x83 ,"ADD  A,E","-"," RES  0,E","res 0,(iy+0)->e","-"},
{0x84 ,"ADD  A,H"," ADD  A,IXH"," RES  0,H","res 0,(iy+0)->h","-"},
{0x85 ,"ADD  A,L"," ADD  A,IXL"," RES  0,L","res 0,(iy+0)->l","-"},
{0x86 ,"ADD  A,(HL)"," ADD  A,(IX+0)"," RES  0,(HL)","RES  0,(IY+0)","-"},
{0x87 ,"ADD  A,A","-"," RES  0,A","res 0,(iy+0)->a","-"},
{0x88 ,"ADC  A,B","-"," RES  1,B","res 1,(iy+0)->b","-"},
{0x89 ,"ADC  A,C","-"," RES  1,C","res 1,(iy+0)->c","-"},
{0x8A ,"ADC  A,D","-"," RES  1,D","res 1,(iy+0)->d","-"},
{0x8B ,"ADC  A,E","-"," RES  1,E","res 1,(iy+0)->e","-"},
{0x8C ,"ADC  A,H"," ADC  A,IXH"," RES  1,H","res 1,(iy+0)->h","-"},
{0x8D ,"ADC  A,L"," ADC  A,IXL"," RES  1,L","res 1,(iy+0)->l","-"},
{0x8E ,"ADC  A,(HL)"," ADC  A,(IX+0)"," RES  1,(HL)","RES  1,(IY+0)","-"},
{0x8F ,"ADC  A,A","-"," RES  1,A","res 1,(iy+0)->a","-"},
{0x90 ,"SUB  A,B","-"," RES  2,B","res 2,(iy+0)->b","-"},
{0x91 ,"SUB  A,C","-"," RES  2,C","res 2,(iy+0)->c","-"},
{0x92 ,"SUB  A,D","-"," RES  2,D","res 2,(iy+0)->d","-"},
{0x93 ,"SUB  A,E","-"," RES  2,E","res 2,(iy+0)->e","-"},
{0x94 ,"SUB  A,H"," SUB  A,IXH"," RES  2,H","res 2,(iy+0)->h","-"},
{0x95 ,"SUB  A,L"," SUB  A,IXL"," RES  2,L","res 2,(iy+0)->l","-"},
{0x96 ,"SUB  A,(HL)"," SUB  A,(IX+0)"," RES  2,(HL)","RES  2,(IY+0)","-"},
{0x97 ,"SUB  A,A","-"," RES  2,A","res 2,(iy+0)->a","-"},
{0x98 ,"SBC  A,B","-"," RES  3,B","res 3,(iy+0)->b","-"},
{0x99 ,"SBC  A,C","-"," RES  3,C","res 3,(iy+0)->c","-"},
{0x9A ,"SBC  A,D","-"," RES  3,D","res 3,(iy+0)->d","-"},
{0x9B ,"SBC  A,E","-"," RES  3,E","res 3,(iy+0)->e","-"},
{0x9C ,"SBC  A,H"," SBC  A,IXH"," RES  3,H","res 3,(iy+0)->h","-"},
{0x9D ,"SBC  A,L"," SBC  A,IXL"," RES  3,L","res 3,(iy+0)->l","-"},
{0x9E ,"SBC  A,(HL)"," SBC  A,(IX+0)"," RES  3,(HL)","RES  3,(IY+0)","-"},
{0x9F ,"SBC  A,A","-"," RES  3,A","res 3,(iy+0)->a","-"},
{0xA0 ,"AND  B","-"," RES  4,B","res 4,(iy+0)->b","LDI"},
{0xA1 ,"AND  C","-"," RES  4,C","res 4,(iy+0)->c","CPI"},
{0xA2 ,"AND  D","-"," RES  4,D","res 4,(iy+0)->d","INI"},
{0xA3 ,"AND  E","-"," RES  4,E","res 4,(iy+0)->e","OTI"},
{0xA4 ,"AND  H"," AND  IXH"," RES  4,H","res 4,(iy+0)->h","-"},
{0xA5 ,"AND  L"," AND  IXL"," RES  4,L","res 4,(iy+0)->l","-"},
{0xA6 ,"AND  (HL)"," AND  (IX+0)"," RES  4,(HL)","RES  4,(IY+0)","-"},
{0xA7 ,"AND  A","-"," RES  4,A","res 4,(iy+0)->a","-"},
{0xA8 ,"XOR  B","-"," RES  5,B","res 5,(iy+0)->b","LDD"},
{0xA9 ,"XOR  C","-"," RES  5,C","res 5,(iy+0)->c","CPD"},
{0xAA ,"XOR  D","-"," RES  5,D","res 5,(iy+0)->d","IND"},
{0xAB ,"XOR  E","-"," RES  5,E","res 5,(iy+0)->e","OTD"},
{0xAC ,"XOR  H"," XOR  IXH"," RES  5,H","res 5,(iy+0)->h","-"},
{0xAD ,"XOR  L"," XOR  IXL"," RES  5,L","res 5,(iy+0)->l","-"},
{0xAE ,"XOR  (HL)"," XOR  (IX+0)"," RES  5,(HL)","RES  5,(IY+0)","-"},
{0xAF ,"XOR  A","-"," RES  5,A","res 5,(iy+0)->a","-"},
{0xB0 ,"OR   B","-"," RES  6,B","res 6,(iy+0)->b","LDIR"},
{0xB1 ,"OR   C","-"," RES  6,C","res 6,(iy+0)->c","CPIR"},
{0xB2 ,"OR   D","-"," RES  6,D","res 6,(iy+0)->d","INIR"},
{0xB3 ,"OR   E","-"," RES  6,E","res 6,(iy+0)->e","OTIR"},
{0xB4 ,"OR   H"," OR   IXH"," RES  6,H","res 6,(iy+0)->h","-"},
{0xB5 ,"OR   L"," OR   IXL"," RES  6,L","res 6,(iy+0)->l","-"},
{0xB6 ,"OR   (HL)"," OR   (IX+0)"," RES  6,(HL)","RES  6,(IY+0)","-"},
{0xB7 ,"OR   A","-"," RES  6,A","res 6,(iy+0)->a","-"},
{0xB8 ,"CP   B","-"," RES  7,B","res 7,(iy+0)->b","LDDR"},
{0xB9 ,"CP   C","-"," RES  7,C","res 7,(iy+0)->c","CPDR"},
{0xBA ,"CP   D","-"," RES  7,D","res 7,(iy+0)->d","INDR"},
{0xBB ,"CP   E","-"," RES  7,E","res 7,(iy+0)->e","OTDR"},
{0xBC ,"CP   H"," CP   IXH"," RES  7,H","res 7,(iy+0)->h","-"},
{0xBD ,"CP   L"," CP   IXL"," RES  7,L","res 7,(iy+0)->l","-"},
{0xBE ,"CP   (HL)"," CP   (IX+0)"," RES  7,(HL)","RES  7,(IY+0)","-"},
{0xBF ,"CP   A","-"," RES  7,A","res 7,(iy+0)->a","-"},
{0xC0 ,"RET  NZ","-"," SET  0,B","set 0,(iy+0)->b","-"},
{0xC1 ,"POP  BC","-"," SET  0,C","set 0,(iy+0)->c","-"},
{0xC2 ,"JP   NZ,&0000","-"," SET  0,D","set 0,(iy+0)->d","-"},
{0xC3 ,"JP   &0000","-"," SET  0,E","set 0,(iy+0)->e","-"},
{0xC4 ,"CALL NZ,&0000","-"," SET  0,H","set 0,(iy+0)->h","-"},
{0xC5 ,"PUSH BC","-"," SET  0,L","set 0,(iy+0)->l","-"},
{0xC6 ,"ADD  A,&00","-"," SET  0,(HL)","SET  0,(IY+0)","-"},
{0xC7 ,"RST  &00","-"," SET  0,A","set 0,(iy+0)->a","-"},
{0xC8 ,"RET  Z","-"," SET  1,B","set 1,(iy+0)->b","-"},
{0xC9 ,"RET","-"," SET  1,C","set 1,(iy+0)->c","-"},
{0xCA ,"JP   Z,&0000","-"," SET  1,D","set 1,(iy+0)->d","-"},
{0xCB ,"**** CB ****","-"," SET  1,E","set 1,(iy+0)->e","-"},
{0xCC ,"CALL Z,&0000","-"," SET  1,H","set 1,(iy+0)->h","-"},
{0xCD ,"CALL &0000","-"," SET  1,L","set 1,(iy+0)->l","-"},
{0xCE ,"ADC  A,&00","-"," SET  1,(HL)","SET  1,(IY+0)","-"},
{0xCF ,"RST  &08","-"," SET  1,A","set 1,(iy+0)->a","-"},
{0xD0 ,"RET  NC","-"," SET  2,B","set 2,(iy+0)->b","-"},
{0xD1 ,"POP  DE","-"," SET  2,C","set 2,(iy+0)->c","-"},
{0xD2 ,"JP   NC,&0000","-"," SET  2,D","set 2,(iy+0)->d","-"},
{0xD3 ,"OUT  (&00),A","-"," SET  2,E","set 2,(iy+0)->e","-"},
{0xD4 ,"CALL NC,&0000","-"," SET  2,H","set 2,(iy+0)->h","-"},
{0xD5 ,"PUSH DE","-"," SET  2,L","set 2,(iy+0)->l","-"},
{0xD6 ,"SUB  A,&00","-"," SET  2,(HL)","SET  2,(IY+0)","-"},
{0xD7 ,"RST  &10","-"," SET  2,A","set 2,(iy+0)->a","-"},
{0xD8 ,"RET  C","-"," SET  3,B","set 3,(iy+0)->b","-"},
{0xD9 ,"EXX","-"," SET  3,C","set 3,(iy+0)->c","-"},
{0xDA ,"JP   C,&0000","-"," SET  3,D","set 3,(iy+0)->d","-"},
{0xDB ,"IN   A,(&00)","-"," SET  3,E","set 3,(iy+0)->e","-"},
{0xDC ,"CALL C,&0000","-"," SET  3,H","set 3,(iy+0)->h","-"},
{0xDD ,"**** DD ****","-"," SET  3,L","set 3,(iy+0)->l","-"},
{0xDE ,"SBC  A,&00","-"," SET  3,(HL)","SET  3,(IY+0)","-"},
{0xDF ,"RST  &18","-"," SET  3,A","set 3,(iy+0)->a","-"},
{0xE0 ,"RET  PO","-"," SET  4,B","set 4,(iy+0)->b","-"},
{0xE1 ,"POP  HL"," POP  IX"," SET  4,C","set 4,(iy+0)->c","-"},
{0xE2 ,"JP   PO,&0000","-"," SET  4,D","set 4,(iy+0)->d","-"},
{0xE3 ,"EX   (SP),HL"," EX   (SP),IX"," SET  4,E","set 4,(iy+0)->e","-"},
{0xE4 ,"CALL PO,&0000","-"," SET  4,H","set 4,(iy+0)->h","-"},
{0xE5 ,"PUSH HL"," PUSH IX"," SET  4,L","set 4,(iy+0)->l","-"},
{0xE6 ,"AND  &00","-"," SET  4,(HL)","SET  4,(IY+0)","-"},
{0xE7 ,"RST  &20","-"," SET  4,A","set 4,(iy+0)->a","-"},
{0xE8 ,"RET  PE","-"," SET  5,B","set 5,(iy+0)->b","-"},
{0xE9 ,"JP   (HL)"," JP   (IX)"," SET  5,C","set 5,(iy+0)->c","-"},
{0xEA ,"JP   PE,&0000","-"," SET  5,D","set 5,(iy+0)->d","-"},
{0xEB ,"EX   DE,HL","-"," SET  5,E","set 5,(iy+0)->e","-"},
{0xEC ,"CALL PE,&0000","-"," SET  5,H","set 5,(iy+0)->h","-"},
{0xED ,"**** ED ****","-"," SET  5,L","set 5,(iy+0)->l","-"},
{0xEE ,"XOR  &00","-"," SET  5,(HL)","SET  5,(IY+0)","-"},
{0xEF ,"RST  &28","-"," SET  5,A","set 5,(iy+0)->a","-"},
{0xF0 ,"RET  P","-"," SET  6,B","set 6,(iy+0)->b","-"},
{0xF1 ,"POP  AF","-"," SET  6,C","set 6,(iy+0)->c","-"},
{0xF2 ,"JP   P,&0000","-"," SET  6,D","set 6,(iy+0)->d","-"},
{0xF3 ,"DI","-"," SET  6,E","set 6,(iy+0)->e","-"},
{0xF4 ,"CALL P,&0000","-"," SET  6,H","set 6,(iy+0)->h","-"},
{0xF5 ,"PUSH AF","-"," SET  6,L","set 6,(iy+0)->l","-"},
{0xF6 ,"OR   &00","-"," SET  6,(HL)","SET  6,(IY+0)","-"},
{0xF7 ,"RST  &30","-"," SET  6,A","set 6,(iy+0)->a","-"},
{0xF8 ,"RET  M","-"," SET  7,B","set 7,(iy+0)->b","[z80]"},
{0xF9 ,"LD   SP,HL","-"," SET  7,C","set 7,(iy+0)->c","[z80]"},
{0xFA ,"JP   M,&0000","-"," SET  7,D","set 7,(iy+0)->d","[z80]"},
{0xFB ,"EI","-"," SET  7,E","set 7,(iy+0)->e","ED_LOAD"},
{0xFC ,"CALL M,&0000","-"," SET  7,H","set 7,(iy+0)->h","[z80]"},
{0xFD ,"**** FD ****","-"," SET  7,L","set 7,(iy+0)->l","[z80]"},
{0xFE ,"CP   &00","-"," SET  7,(HL)","SET  7,(IY+0)","[z80]"},
{0xff ,"RST  &38","-","SET  7,A","set 7,(iy+0)->a","ED_DOS"}
/*
Notes on index registers
------------------------
Where DD and IX are mentioned, FD and IY may be substituted and vis versa.
    
Notes on Indexed Shift/Bit Operations
-------------------------------------
A shift or bit operation on an indexed byte in memory is done by prefixing
a CB opcode refering to (HL) with DD or FD to specify (IX+n) or (IY+n). 
If the CB opcode does not refer to (HL), slightly differing things happen.
The majority of Z80 CPUs execute them as shown; the shift or bit operation
is done on and indexed byte in memory, and then if the opcode does not
specify (HL) originally, the resultant byte is copied into the specified
register.  This is summarised with this example:
       CB 0x    RLC r          FD CB nn 0x     RLC (IY+nn)->r
       for x=0..5, 7 for r=B,C,D,E,H,L,A
  
Some CPUs allow access to the high and low halves of the index register,
if x is 4 or 5, the operation does RLC IYH or RLC IYH.
       CB 04   RLC H           FD CB nn 04     RLC IYH
       CB 05   RLC L           FD CB nn 05     RLC IYL
    
Some CPUs treat all the subcodes as accessing the indexed byte and nothing
else:
       CB 0x   RLC r           FD CB nn 0X     RLC (IY+nn)
                               for all x=0..7
    
Notes on ED opcodes
-------------------
J.G.Harston's !Z80Tube Z80 CoPro emulator includes the extra opcodes ED00
to ED0F to interface with the host.  G.A.Lunter's Z80 Spectrum emulator
includes the extra opcodes EDF8 to EDFF to interface to the host.          
Full Z80 Opcode List Including Undocumented Opcodes
          ===================================================
               File: DOCS.Comp.Z80.OpList - Update: 0.10
                Author: J.G.Harston - Date: 09-09-1997
*/
