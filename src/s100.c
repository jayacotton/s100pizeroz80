// S100 Bus Interface for the Raspberry Pi S100board (John Monahan S100Computers.com)
//      
//      V0.1                    4/4/2022        Start of display port address working
//      V.1.1                   5/1/2022        Start Display RAM       
//      V1.12                   5/10/2022       Added console input source.
//      V1.13                   6/6/2022        Added monitor commands
//      V1.31                   6/24/2022       Added interrupts



// Notes:-
// You can use the printf() function to display feedback text messages in the Eclipse Console window.
// However if they are too rapid/long the S100 system seems to get out of sync.
// They are however very useful for debugging.
//
#include <stdio.h>
#include <wiringPi.h>
#include <ctype.h>

#define LOW 0
#define HIGH 1
#define ESC  0x1b
#define CR   0x0d
#define LF   0x0a
#define BS   0x08
#define BELL 0x07
#define SP   0x20
#define DEL  0x7f

#define TEST1 FALSE		// Set TRUE to increase from 0 to FFFFF the S100 Bus address lines (Can be monitored with SMB)
#define TEST2 FALSE		// Set TRUE to continuously 0123456789 the S100 Bus console out port (01H)
#define TEST3 FALSE		// Read a keyboard character and print it on screen



										// These three tests are used only initially to check/debug the hardware
#define SerialBoardPresent FALSE	// If serial board for speech synthesis is present
#define IOBYTE  0xEF		// S100 Bus IOBYTE Port on V3 SMB Board
#define CON_OUT_PORT 1		// Port 1 on Propeller driven Console I/O Board
#define CON_IN_PORT 1		// Port 1 on Propeller driven Console I/O Board
#define CON_STATUS_PORT 0	// Port 0 on Propeller driven Console I/O Board
#define BCTL 0xA0		// Serial board speaker CTL port (Zilog SCC Chip)
#define BDTA 0xA2		// Speaker data port
#define RESET_PORT 0xdd		// Port to reset things back to the Z80bus master

#define DATA_A0	2		// GPIO2 Raspberry Pi Zero Pin 3
#define DATA_A1	3		// GPIO3 Raspberry Pi Zero Pin 5
#define DATA_A2	4		// GPIO4 Raspberry Pi Zero Pin 7
#define DATA_A3 5		// GPIO5 Raspberry Pi Zero Pin 29
#define DATA_A4 6		// GPIO6 Raspberry Pi Zero Pin 31
#define DATA_A5 7		// GPIO7 Raspberry Pi Zero Pin 26
#define DATA_A6 8		// GPIO8 Raspberry Pi Zero Pin 24
#define DATA_A7 9		// GPIO9 Raspberry Pi Zero Pin 21

#define DATA_A8	2		// GPIO2 Raspberry Pi Zero Pin 3
#define DATA_A9	3		// GPIO3 Raspberry Pi Zero Pin 5
#define DATA_A10 4		// GPIO4 Raspberry Pi Zero Pin 7
#define DATA_A11 5		// GPIO5 Raspberry Pi Zero Pin 29
#define DATA_A12 6		// GPIO6 Raspberry Pi Zero Pin 31
#define DATA_A13 7		// GPIO7 Raspberry Pi Zero Pin 26
#define DATA_A14 8		// GPIO8 Raspberry Pi Zero Pin 24
#define DATA_A15 9		// GPIO9 Raspberry Pi Zero Pin 21

#define DATA_A16 2		// GPIO2 Raspberry Pi Zero Pin 3
#define DATA_A17 3		// GPIO3 Raspberry Pi Zero Pin 5
#define DATA_A18 4		// GPIO4 Raspberry Pi Zero Pin 7
#define DATA_A19 5		// GPIO5 Raspberry Pi Zero Pin 29
#define DATA_A20 6		// GPIO6 Raspberry Pi Zero Pin 31
#define DATA_A21 7		// GPIO7 Raspberry Pi Zero Pin 26
#define DATA_A22 8		// GPIO8 Raspberry Pi Zero Pin 24
#define DATA_A23 9		// GPIO9 Raspberry Pi Zero Pin 21

#define DATA_IO0 16		// GPIO16 Raspberry Pi Zero Pin 36
#define DATA_IO1 17		// GPIO17 Raspberry Pi Zero Pin 11
#define DATA_IO2 18		// GPIO18 Raspberry Pi Zero Pin 12
#define DATA_IO3 19		// GPIO19 Raspberry Pi Zero Pin 35
#define DATA_IO4 20		// GPIO20 Raspberry Pi Zero Pin 38
#define DATA_IO5 21		// GPIO21 Raspberry Pi Zero Pin 4
#define DATA_IO6 22		// GPIO22 Raspberry Pi Zero Pin 15
#define DATA_IO7 23		// GPIO23 Raspberry Pi Zero Pin 16

#define DATA_II0 16		// GPIO16 Raspberry Pi Zero Pin 36
#define DATA_II1 17		// GPIO17 Raspberry Pi Zero Pin 11
#define DATA_II2 18		// GPIO18 Raspberry Pi Zero Pin 12
#define DATA_II3 19		// GPIO19 Raspberry Pi Zero Pin 35
#define DATA_II4 20		// GPIO20 Raspberry Pi Zero Pin 38
#define DATA_II5 21		// GPIO21 Raspberry Pi Zero Pin 4
#define DATA_II6 22		// GPIO22 Raspberry Pi Zero Pin 15
#define DATA_II7 23		// GPIO23 Raspberry Pi Zero Pin 16

#define ADD_LOW 25		// GPIO25 Raspberry Pi Zero Pin 22
#define ADD_HIGH 24		// GPIO24 Raspberry Pi Zero Pin 18
#define ADD_EXT 12		// GPIO12 Raspberry Pi Zero Pin 32
#define STATUS 10		// GPIO10 Raspberry Pi Zero Pin 19
#define CTL 0			// GPIO0 Raspberry Pi Zero Pin 27
#define WRITE_DATA 1		// GPIO1 Raspberry Pi Zero Pin 28
#define READ_DATA  13		// GPIO13 Raspberry Pi Zero Pin 33

#define MWRT 2			// GPIO2 Raspberry Pi Zero Pin 3
#define sHLTA 3			// GPIO3 Raspberry Pi Zero Pin 5
#define sINTA 4			// GPIO4 Raspberry Pi Zero Pin 7
#define sWO 5			// GPIO5 Raspberry Pi Zero Pin 29
#define sM1 6			// GPIO6 Raspberry Pi Zero Pin 31
#define sOUT 7			// GPIO7 Raspberry Pi Zero Pin 26
#define sINP 8			// GPIO8 Raspberry Pi Zero Pin 24
#define sMEMR 9			// GPIO8 Raspberry Pi Zero Pin 21

#define pSYNC 2			// GPIO2 Raspberry Pi Zero Pin 3
#define pWR 3			// GPIO3 Raspberry Pi Zero Pin 5
#define pSTVAL 4		// GPIO4 Raspberry Pi Zero Pin 7
#define pDBIN 5			// GPIO5 Raspberry Pi Zero Pin 29
#define sXTRQ 6			// GPIO6 Raspberry Pi Zero Pin 31
#define CLEAR_INT 7		// GPIO7 Raspberry Pi Zero Pin 26
#define S100_INT 15		// GPI15 Raspberry Pi Zero Pin 10
#define INPUT_INT 26		// GPI26 Raspberry Pi Zero Pin 37



#define ACTIVE 11		// GPIO11 Raspberry Pi Zero Pin 32
#define RESET 27		// GPIO27 Raspberry Pi Zero Pin 36
#define CONSOLE_FLAG 14		// GPIO14 Determines if Console input is S100bus or Raspberry)

int Interrupt_Flag;
int Interrupts_Active;		// If True Interrupts will be detected and flagged
int AbortFlag;
char buffer[1024];
char char_buffer[200];

void EndBusCycle();
char ReadRAM(int);
void WriteRAM(int, int);
void S100_pSYNC();
void PrintString();
void PutChar(char);
void PutCRLF();
char GetChar();
void QueryPort();
int GetHexValue();		// Return a int HEX value from keyboard
char ReadPort(int);
void WritePort(int, int);
void Show_RAM_Map();
void GetHex2Values(int *, int *);
void GetHex3Values(int *, int *, int *);
void DisplayRAM();
void DisplayRAM_ASCII();
void Echo();
void S100Signals();
void halt();
void FillRAM();
void MoveRAM();
void SubstituteRAM();

int ConsoleStatusIn();
int ConsoleStatusOut();
int ConsoleDataIn();
void ConsoleDataOut(int);
int SpeakString(char *);
int SpeakOut(char);
int Send_Z80Reset();
void DisplayRAM_ASCII();
void VerifyRAM();
void ShortDelay(int);

void IntSignalOn();
void IntSignalOff();
int CheckForInterrupts();	// If the was an interrupt , if so process it
void ClearInterrupts();
int ReadIntVector();
void Send_sINTA();
void PrintBits(int);
void PrintIntNummber(int);


int s100_init()
{
    int j;
    wiringPiSetupGpio();

    pinMode(DATA_A0, OUTPUT);	//Data Out
    pinMode(DATA_A1, OUTPUT);
    pinMode(DATA_A2, OUTPUT);
    pinMode(DATA_A3, OUTPUT);
    pinMode(DATA_A4, OUTPUT);
    pinMode(DATA_A5, OUTPUT);
    pinMode(DATA_A6, OUTPUT);
    pinMode(DATA_A7, OUTPUT);

    pinMode(DATA_IO0, INPUT);	//Data Out or In  (Default INPUT)
    pinMode(DATA_IO1, INPUT);
    pinMode(DATA_IO2, INPUT);
    pinMode(DATA_IO3, INPUT);
    pinMode(DATA_IO4, INPUT);
    pinMode(DATA_IO5, INPUT);
    pinMode(DATA_IO6, INPUT);
    pinMode(DATA_IO7, INPUT);


    pinMode(ADD_LOW, OUTPUT);	//Latches
    pinMode(ADD_HIGH, OUTPUT);
    pinMode(ADD_EXT, OUTPUT);
    pinMode(STATUS, OUTPUT);
    pinMode(CTL, OUTPUT);

    pinMode(WRITE_DATA, OUTPUT);
    pinMode(READ_DATA, OUTPUT);
    pinMode(INPUT_INT, OUTPUT);

    pinMode(ACTIVE, INPUT);	//BOARD ACTIVE
    pinMode(RESET, INPUT);	//RESET*
    pinMode(CONSOLE_FLAG, INPUT);	//Determines if Console input is S100bus or Raspberry)

    //Inactivate all signals
    digitalWrite(ADD_LOW, LOW);	//low Address
    digitalWrite(ADD_HIGH, LOW);	//High Address
    digitalWrite(ADD_EXT, LOW);	//Extended Address
    digitalWrite(STATUS, LOW);	//Status Lines
    digitalWrite(CTL, LOW);	//Control lines
    digitalWrite(WRITE_DATA, LOW);	// WRITE DATA STROBE
    digitalWrite(READ_DATA, LOW);	// READ DATA LATCH

    digitalWrite(INPUT_INT, HIGH);	// S100 Ints

    AbortFlag = 0;

}

int Send_Z80Reset()
{
    int in_value;

    in_value = ReadPort(RESET_PORT);
    return in_value;
}

/* this code is intended to replace the original address
setup code int ReadRAM and WriteRAM.

There are three 8 bit registers used to hold the 24bit RAM
address */

static int PinAddr1[] = {
    DATA_A0, DATA_A1, DATA_A2, DATA_A3,
    DATA_A4, DATA_A5, DATA_A6, DATA_A7
};

static int PinAddr2[] = {
    DATA_A8, DATA_A9, DATA_A10, DATA_A11,
    DATA_A12, DATA_A13, DATA_A14, DATA_A15
};

static int PinAddr3[] = {
    DATA_A16, DATA_A17, DATA_A18, DATA_A19,
    DATA_A20, DATA_A21, DATA_A22, DATA_A23
};

unsigned int low, mid, high;
unsigned long last;
void SetAddress(unsigned int location)
{
    int i;
    int k = 0;

//  if (last == location)
    //   return;
//  last = location;


#ifdef NEVER

    if (low != (location & 0xff)) {
	low = location & 0xff;
	k = low;
	for (i = 0; i < 8; i++) {
	    (k & 1) ? digitalWrite(PinAddr1[i],
				   HIGH) : digitalWrite(PinAddr1[i], LOW);
	    k = k >> 1;
	}
    }
	digitalWrite(ADD_LOW, HIGH);	//Latch low address lines
	digitalWrite(ADD_LOW, LOW);
    if (mid != ((location >> 8) & 0xff)) {
	mid = (location >> 8) & 0xff;
	k = mid;
	for (i = 0; i < 8; i++) {
	    (location & 1) ? digitalWrite(PinAddr2[i],
					  HIGH) : digitalWrite(PinAddr2[i],
							       LOW);
	    k = k >> 1;
	}
    }
	digitalWrite(ADD_HIGH, HIGH);	//Latch high address lines
	digitalWrite(ADD_HIGH, LOW);
    if (high != ((location >> 16) & 0xff)) {
	high = (location >> 16) & 0xff;
	k = high;
	for (i = 0; i < 8; i++) {
	    (location & 1) ? digitalWrite(PinAddr3[i],
					  HIGH) : digitalWrite(PinAddr3[i],
							       LOW);
	    k = k >> 1;
	}
    }
	digitalWrite(ADD_EXT, HIGH);	//Latch extended address lines
	digitalWrite(ADD_EXT, LOW);
#else
    (location & 0b1) ? digitalWrite(DATA_A0, HIGH) : digitalWrite(DATA_A0,
								   LOW);
    (location & 0b10) ? digitalWrite(DATA_A1,
				      HIGH) : digitalWrite(DATA_A1, LOW);
    (location & 0b100) ? digitalWrite(DATA_A2,
				       HIGH) : digitalWrite(DATA_A2, LOW);
    (location & 0b1000) ? digitalWrite(DATA_A3,
					HIGH) : digitalWrite(DATA_A3, LOW);
    (location & 0b10000) ? digitalWrite(DATA_A4,
					 HIGH) : digitalWrite(DATA_A4,
							      LOW);
    (location & 0b100000) ? digitalWrite(DATA_A5,
					  HIGH) : digitalWrite(DATA_A5,
							       LOW);
    (location & 0b1000000) ? digitalWrite(DATA_A6,
					   HIGH) : digitalWrite(DATA_A6,
								LOW);
    (location & 0b10000000) ? digitalWrite(DATA_A7,
					    HIGH) : digitalWrite(DATA_A7,
								 LOW);

    digitalWrite(ADD_LOW, HIGH);	//Latch low address lines
    digitalWrite(ADD_LOW, LOW);


    (location & 0b100000000) ? digitalWrite(DATA_A8,
					     HIGH) : digitalWrite(DATA_A8,
								  LOW);
    (location & 0b1000000000) ? digitalWrite(DATA_A9,
					      HIGH) : digitalWrite(DATA_A9,
								   LOW);
    (location & 0b10000000000) ? digitalWrite(DATA_A10,
					       HIGH) :
	digitalWrite(DATA_A10, LOW);
    (location & 0b100000000000) ? digitalWrite(DATA_A11,
						HIGH) :
	digitalWrite(DATA_A11, LOW);
    (location & 0b1000000000000) ? digitalWrite(DATA_A12,
						 HIGH) :
	digitalWrite(DATA_A12, LOW);
    (location & 0b10000000000000) ? digitalWrite(DATA_A13,
						  HIGH) :
	digitalWrite(DATA_A13, LOW);
    (location & 0b100000000000000) ? digitalWrite(DATA_A14,
						   HIGH) :
	digitalWrite(DATA_A14, LOW);
    (location & 0b1000000000000000) ? digitalWrite(DATA_A15,
						    HIGH) :
	digitalWrite(DATA_A15, LOW);
    digitalWrite(ADD_HIGH, HIGH);	//Latch high address lines
    digitalWrite(ADD_HIGH, LOW);

    (location & 0b10000000000000000) ? digitalWrite(DATA_A16,
						     HIGH) :
	digitalWrite(DATA_A16, LOW);
    (location & 0b100000000000000000) ? digitalWrite(DATA_A17,
						      HIGH) :
	digitalWrite(DATA_A17, LOW);
    (location & 0b1000000000000000000) ? digitalWrite(DATA_A18,
						       HIGH) :
	digitalWrite(DATA_A18, LOW);
    (location & 0b10000000000000000000) ? digitalWrite(DATA_A19,
							HIGH) :
	digitalWrite(DATA_A19, LOW);
    (location & 0b100000000000000000000) ? digitalWrite(DATA_A20,
							 HIGH) :
	digitalWrite(DATA_A20, LOW);
    (location & 0b1000000000000000000000) ? digitalWrite(DATA_A21,
							  HIGH) :
	digitalWrite(DATA_A21, LOW);
    (location & 0b10000000000000000000000) ? digitalWrite(DATA_A22,
							   HIGH) :
	digitalWrite(DATA_A22, LOW);
    (location & 0b100000000000000000000000) ? digitalWrite(DATA_A23,
							    HIGH) :
	digitalWrite(DATA_A23, LOW);
    digitalWrite(ADD_EXT, HIGH);	//Latch extended address lines
    digitalWrite(ADD_EXT, LOW);
#endif
}

char ReadRAM(int location)	// Set S100bus address lines A0-A23 to a value (24 bits wide)
{				// Remember location is a int
    int i;
    int k = 0;

    SetAddress(location);

    S100_pSYNC();

    digitalWrite(MWRT, LOW);	// GPIO2 Raspberry Pi Zero Pin 3
    digitalWrite(sHLTA, LOW);	// GPIO3 Raspberry Pi Zero Pin 5                                        
    digitalWrite(sINTA, LOW);	// GPIO4 Raspberry Pi Zero Pin 7                                        
    digitalWrite(sWO, LOW);	// GPIO5 Raspberry Pi Zero Pin 29                                       
    digitalWrite(sM1, LOW);	// GPIO6 Raspberry Pi Zero Pin 31                       
    digitalWrite(sOUT, LOW);	// GPIO7 Raspberry Pi Zero Pin 26
    digitalWrite(sINP, LOW);	// GPIO8 Raspberry Pi Zero Pin 24
    digitalWrite(sMEMR, HIGH);	//HIGH                  // GPIO9 Raspberry Pi Zero Pin 21
    digitalWrite(sMEMR, HIGH);	//HIGH                  // GPIO9 Raspberry Pi Zero Pin 21

    digitalWrite(STATUS, HIGH);	// GPIO10 Raspberry Pi Zero Pin 19
    digitalWrite(STATUS, LOW);	// GPIO10 Raspberry Pi Zero Pin 19

    digitalWrite(READ_DATA, HIGH);	// GPIO13 Raspberry Pi Zero Pin 33

    digitalWrite(pSYNC, LOW);	// GPIO2 Raspberry Pi Zero Pin 3
    digitalWrite(pWR, HIGH);	// GPIO3 Raspberry Pi Zero Pin 5                                        
    digitalWrite(pSTVAL, HIGH);	// GPIO4 Raspberry Pi Zero Pin 7                                        
    digitalWrite(pDBIN, HIGH);	//HIGH                  // GPIO5 Raspberry Pi Zero Pin 29                                       
    digitalWrite(pDBIN, HIGH);	//HIGH                  // GPIO5 Raspberry Pi Zero Pin 29                                       
    digitalWrite(sXTRQ, HIGH);	// GPIO6 Raspberry Pi Zero Pin 31                       
    digitalWrite(CLEAR_INT, HIGH);	// GPIO7 Raspberry Pi Zero Pin 26

    digitalWrite(CTL, HIGH);	// GPIO0 Raspberry Pi Zero Pin 27
    digitalWrite(CTL, LOW);	// GPIO0 Raspberry Pi Zero Pin 27       


    k = 0;
    if (digitalRead(DATA_II0))
	k = 1;
    if (digitalRead(DATA_II1))
	k |= 0b10;
    if (digitalRead(DATA_II2))
	k |= 0b100;
    if (digitalRead(DATA_II3))
	k |= 0b1000;
    if (digitalRead(DATA_II4))
	k |= 0b10000;
    if (digitalRead(DATA_II5))
	k |= 0b100000;
    if (digitalRead(DATA_II6))
	k |= 0b1000000;
    if (digitalRead(DATA_II7))
	k |= 0b10000000;

    digitalWrite(READ_DATA, LOW);	// GPIO13 Raspberry Pi Zero Pin 33
    EndBusCycle();
    return (char) k;
}



void WriteRAM(int location, int value)	// Set S100bus address lines A0-A23 to a value (24 bits wide)
{				// Remember location is a long
    int i;
    int k = 0;

    SetAddress(location);

    pinMode(DATA_IO0, OUTPUT);	//Data Out (Default was INPUT)
    pinMode(DATA_IO1, OUTPUT);
    pinMode(DATA_IO2, OUTPUT);
    pinMode(DATA_IO3, OUTPUT);
    pinMode(DATA_IO4, OUTPUT);
    pinMode(DATA_IO5, OUTPUT);
    pinMode(DATA_IO6, OUTPUT);
    pinMode(DATA_IO7, OUTPUT);


    for (i = 0; i < 8; i++)	// Setup data
    {
	k = ((value >> i) & 1);
	if (i == 0) {
	    if (k)
		digitalWrite(DATA_II0, HIGH);
	    else
		digitalWrite(DATA_II0, LOW);
	} else if (i == 1) {	// GPIO17 Raspberry Pi Zero Pin 11
	    if (k)
		digitalWrite(DATA_II1, HIGH);
	    else
		digitalWrite(DATA_II1, LOW);
	} else if (i == 2) {
	    if (k)
		digitalWrite(DATA_II2, HIGH);
	    else
		digitalWrite(DATA_II2, LOW);
	} else if (i == 3) {
	    if (k)
		digitalWrite(DATA_II3, HIGH);
	    else
		digitalWrite(DATA_II3, LOW);
	} else if (i == 4) {
	    if (k)
		digitalWrite(DATA_II4, HIGH);
	    else
		digitalWrite(DATA_II4, LOW);
	} else if (i == 5) {
	    if (k)
		digitalWrite(DATA_II5, HIGH);
	    else
		digitalWrite(DATA_II5, LOW);
	} else if (i == 6) {
	    if (k)
		digitalWrite(DATA_II6, HIGH);
	    else
		digitalWrite(DATA_II6, LOW);
	} else if (i == 7) {
	    if (k)
		digitalWrite(DATA_II7, HIGH);
	    else
		digitalWrite(DATA_II7, LOW);
	}
    }


    S100_pSYNC();

    digitalWrite(MWRT, HIGH);	//HIGH                  // GPIO2 Raspberry Pi Zero Pin 3
    digitalWrite(MWRT, HIGH);	//HIGH                  // GPIO2 Raspberry Pi Zero Pin 3
    digitalWrite(sHLTA, LOW);	// GPIO3 Raspberry Pi Zero Pin 5                                        
    digitalWrite(sINTA, LOW);	// GPIO4 Raspberry Pi Zero Pin 7                                        
    digitalWrite(sWO, HIGH);	// GPIO5 Raspberry Pi Zero Pin 29                                       
    digitalWrite(sM1, LOW);	// GPIO6 Raspberry Pi Zero Pin 31                       
    digitalWrite(sOUT, LOW);	// GPIO7 Raspberry Pi Zero Pin 26
    digitalWrite(sINP, LOW);	// GPIO8 Raspberry Pi Zero Pin 24
    digitalWrite(sMEMR, LOW);	// GPIO9 Raspberry Pi Zero Pin 21

    digitalWrite(STATUS, HIGH);	// GPIO10 Raspberry Pi Zero Pin 19
    digitalWrite(STATUS, LOW);	// GPIO10 Raspberry Pi Zero Pin 19

    digitalWrite(WRITE_DATA, HIGH);	// GPIO13 Raspberry Pi Zero Pin 33

    digitalWrite(pSYNC, LOW);	// GPIO2 Raspberry Pi Zero Pin 3
    digitalWrite(pWR, LOW);	//LOW                   // GPIO3 Raspberry Pi Zero Pin 5                                        
    digitalWrite(pWR, LOW);	//LOW                   // GPIO3 Raspberry Pi Zero Pin 5                                        
    digitalWrite(pSTVAL, HIGH);	// GPIO4 Raspberry Pi Zero Pin 7                                        
    digitalWrite(pDBIN, LOW);	// GPIO5 Raspberry Pi Zero Pin 29                                       
    digitalWrite(sXTRQ, HIGH);	// GPIO6 Raspberry Pi Zero Pin 31                       
    digitalWrite(CLEAR_INT, HIGH);	// GPIO7 Raspberry Pi Zero Pin 26

    digitalWrite(CTL, HIGH);	// GPIO0 Raspberry Pi Zero Pin 27
    digitalWrite(CTL, LOW);	// GPIO0 Raspberry Pi Zero Pin 27       

    digitalWrite(WRITE_DATA, LOW);	// GPIO13 Raspberry Pi Zero Pin 33
    EndBusCycle();

    pinMode(DATA_IO0, INPUT);	//Data Out or In  (Default INPUT)
    pinMode(DATA_IO1, INPUT);
    pinMode(DATA_IO2, INPUT);
    pinMode(DATA_IO3, INPUT);
    pinMode(DATA_IO4, INPUT);
    pinMode(DATA_IO5, INPUT);
    pinMode(DATA_IO6, INPUT);
    pinMode(DATA_IO7, INPUT);

    return;
}



char ReadPort(int location)	// Set S100bus address lines A0-A15 to a value (24 bits wide)
{				// Remember location is a int
    int i;
    int k = 0;

    for (i = 0; i < 16; i++) {
	k = ((location >> i) & 1);
	if (i == 0) {
	    if (k)
		digitalWrite(DATA_A0, HIGH);
	    else
		digitalWrite(DATA_A0, LOW);
	} else if (i == 1) {
	    if (k)
		digitalWrite(DATA_A1, HIGH);
	    else
		digitalWrite(DATA_A1, LOW);
	} else if (i == 2) {
	    if (k)
		digitalWrite(DATA_A2, HIGH);
	    else
		digitalWrite(DATA_A2, LOW);
	} else if (i == 3) {
	    if (k)
		digitalWrite(DATA_A3, HIGH);
	    else
		digitalWrite(DATA_A3, LOW);
	} else if (i == 4) {
	    if (k)
		digitalWrite(DATA_A4, HIGH);
	    else
		digitalWrite(DATA_A4, LOW);
	} else if (i == 5) {
	    if (k)
		digitalWrite(DATA_A5, HIGH);
	    else
		digitalWrite(DATA_A5, LOW);
	} else if (i == 6) {
	    if (k)
		digitalWrite(DATA_A6, HIGH);
	    else
		digitalWrite(DATA_A6, LOW);
	} else if (i == 7) {
	    if (k)
		digitalWrite(DATA_A7, HIGH);
	    else
		digitalWrite(DATA_A7, LOW);
	    digitalWrite(ADD_LOW, HIGH);	//Latch low address lines
	    digitalWrite(ADD_LOW, LOW);
	}



	else if (i == 8) {
	    if (k)
		digitalWrite(DATA_A8, HIGH);
	    else
		digitalWrite(DATA_A8, LOW);
	} else if (i == 9) {
	    if (k)
		digitalWrite(DATA_A9, HIGH);
	    else
		digitalWrite(DATA_A9, LOW);
	} else if (i == 10) {
	    if (k)
		digitalWrite(DATA_A10, HIGH);
	    else
		digitalWrite(DATA_A10, LOW);
	} else if (i == 11) {
	    if (k)
		digitalWrite(DATA_A11, HIGH);
	    else
		digitalWrite(DATA_A11, LOW);
	} else if (i == 12) {
	    if (k)
		digitalWrite(DATA_A12, HIGH);
	    else
		digitalWrite(DATA_A12, LOW);
	} else if (i == 13) {
	    if (k)
		digitalWrite(DATA_A13, HIGH);
	    else
		digitalWrite(DATA_A13, LOW);
	} else if (i == 14) {
	    if (k)
		digitalWrite(DATA_A14, HIGH);
	    else
		digitalWrite(DATA_A14, LOW);
	} else if (i == 15) {
	    if (k)
		digitalWrite(DATA_A15, HIGH);
	    else
		digitalWrite(DATA_A15, LOW);
	    digitalWrite(ADD_HIGH, HIGH);	//Latch high address lines
	    digitalWrite(ADD_HIGH, LOW);
	}
    }
    S100_pSYNC();
    digitalWrite(READ_DATA, HIGH);	// GPIO13 Raspberry Pi Zero Pin 33

    digitalWrite(MWRT, LOW);	// GPIO2 Raspberry Pi Zero Pin 3
    digitalWrite(sHLTA, LOW);	// GPIO3 Raspberry Pi Zero Pin 5                                        
    digitalWrite(sINTA, LOW);	// GPIO4 Raspberry Pi Zero Pin 7                                        
    digitalWrite(sWO, LOW);	// GPIO5 Raspberry Pi Zero Pin 29                                       
    digitalWrite(sM1, LOW);	// GPIO6 Raspberry Pi Zero Pin 31                       
    digitalWrite(sOUT, LOW);	// GPIO7 Raspberry Pi Zero Pin 26
    digitalWrite(sINP, HIGH);	//// HIGH                       // GPIO8 Raspberry Pi Zero Pin 24
    digitalWrite(sMEMR, LOW);	// GPIO9 Raspberry Pi Zero Pin 21

    digitalWrite(STATUS, HIGH);	// GPIO10 Raspberry Pi Zero Pin 19
    digitalWrite(STATUS, LOW);	// GPIO10 Raspberry Pi Zero Pin 19

    digitalWrite(pSYNC, LOW);	// GPIO2 Raspberry Pi Zero Pin 3
    digitalWrite(pWR, HIGH);	// GPIO3 Raspberry Pi Zero Pin 5                                        
    digitalWrite(pSTVAL, HIGH);	// GPIO4 Raspberry Pi Zero Pin 7                                        
    digitalWrite(pDBIN, HIGH);	///// HIGH                      // GPIO5 Raspberry Pi Zero Pin 29                                       
    digitalWrite(sXTRQ, HIGH);	// GPIO6 Raspberry Pi Zero Pin 31                       
    digitalWrite(CLEAR_INT, HIGH);	// GPIO7 Raspberry Pi Zero Pin 26

    digitalWrite(CTL, HIGH);	// GPIO0 Raspberry Pi Zero Pin 27
    digitalWrite(CTL, LOW);	// GPIO0 Raspberry Pi Zero Pin 27       


    for (i = 0; i < 8; i++)	// First set direction of Edison bits to READ
    {
	if (i == 0) {
	    if (digitalRead(DATA_II0))	// GPIO16 Raspberry Pi Zero Pin 36
		k = 1;
	    else
		k = 0;
	} else if (i == 1) {	// GPIO17 Raspberry Pi Zero Pin 11
	    if (digitalRead(DATA_II1))
		k |= 0b00000010;
	} else if (i == 2) {
	    if (digitalRead(DATA_II2))	// GPIO18 Raspberry Pi Zero Pin 12
		k |= 0b00000100;
	} else if (i == 3) {
	    if (digitalRead(DATA_II3))	// GPIO19 Raspberry Pi Zero Pin 35
		k |= 0b00001000;
	} else if (i == 4) {
	    if (digitalRead(DATA_II4))	// GPIO20 Raspberry Pi Zero Pin 38
		k |= 0b00010000;
	} else if (i == 5) {
	    if (digitalRead(DATA_II5))	// GPIO21 Raspberry Pi Zero Pin 4
		k |= 0b00100000;
	} else if (i == 6) {
	    if (digitalRead(DATA_II6))	// GPIO22 Raspberry Pi Zero Pin 15
		k |= 0b01000000;
	} else if (i == 7) {
	    if (digitalRead(DATA_II7))	// GPIO23 Raspberry Pi Zero Pin 16
		k |= 0b10000000;
	}
    }
    digitalWrite(READ_DATA, LOW);	// GPIO13 Raspberry Pi Zero Pin 33
    EndBusCycle();
    return k;
}


void WritePort(int location, int value)	// Set S100bus address lines A0-A15 to a value (24 bits wide)
{				// Remember location is a int
    int i;
    int k = 0;

    for (i = 0; i < 16; i++) {
	k = ((location >> i) & 1);
	if (i == 0) {
	    if (k)
		digitalWrite(DATA_A0, HIGH);
	    else
		digitalWrite(DATA_A0, LOW);
	} else if (i == 1) {
	    if (k)
		digitalWrite(DATA_A1, HIGH);
	    else
		digitalWrite(DATA_A1, LOW);
	} else if (i == 2) {
	    if (k)
		digitalWrite(DATA_A2, HIGH);
	    else
		digitalWrite(DATA_A2, LOW);
	} else if (i == 3) {
	    if (k)
		digitalWrite(DATA_A3, HIGH);
	    else
		digitalWrite(DATA_A3, LOW);
	} else if (i == 4) {
	    if (k)
		digitalWrite(DATA_A4, HIGH);
	    else
		digitalWrite(DATA_A4, LOW);
	} else if (i == 5) {
	    if (k)
		digitalWrite(DATA_A5, HIGH);
	    else
		digitalWrite(DATA_A5, LOW);
	} else if (i == 6) {
	    if (k)
		digitalWrite(DATA_A6, HIGH);
	    else
		digitalWrite(DATA_A6, LOW);
	} else if (i == 7) {
	    if (k)
		digitalWrite(DATA_A7, HIGH);
	    else
		digitalWrite(DATA_A7, LOW);
	    digitalWrite(ADD_LOW, HIGH);	//Latch low address lines
	    digitalWrite(ADD_LOW, LOW);
	}



	else if (i == 8) {
	    if (k)
		digitalWrite(DATA_A8, HIGH);
	    else
		digitalWrite(DATA_A8, LOW);
	} else if (i == 9) {
	    if (k)
		digitalWrite(DATA_A9, HIGH);
	    else
		digitalWrite(DATA_A9, LOW);
	} else if (i == 10) {
	    if (k)
		digitalWrite(DATA_A10, HIGH);
	    else
		digitalWrite(DATA_A10, LOW);
	} else if (i == 11) {
	    if (k)
		digitalWrite(DATA_A11, HIGH);
	    else
		digitalWrite(DATA_A11, LOW);
	} else if (i == 12) {
	    if (k)
		digitalWrite(DATA_A12, HIGH);
	    else
		digitalWrite(DATA_A12, LOW);
	} else if (i == 13) {
	    if (k)
		digitalWrite(DATA_A13, HIGH);
	    else
		digitalWrite(DATA_A13, LOW);
	} else if (i == 14) {
	    if (k)
		digitalWrite(DATA_A14, HIGH);
	    else
		digitalWrite(DATA_A14, LOW);
	} else if (i == 15) {
	    if (k)
		digitalWrite(DATA_A15, HIGH);
	    else
		digitalWrite(DATA_A15, LOW);
	    digitalWrite(ADD_HIGH, HIGH);	//Latch high address lines
	    digitalWrite(ADD_HIGH, LOW);
	}
    }

    pinMode(DATA_IO0, OUTPUT);	//Data Out (Default INPUT)
    pinMode(DATA_IO1, OUTPUT);
    pinMode(DATA_IO2, OUTPUT);
    pinMode(DATA_IO3, OUTPUT);
    pinMode(DATA_IO4, OUTPUT);
    pinMode(DATA_IO5, OUTPUT);
    pinMode(DATA_IO6, OUTPUT);
    pinMode(DATA_IO7, OUTPUT);

    for (i = 0; i < 8; i++)	// Setup data
    {
	k = ((value >> i) & 1);
	if (i == 0) {
	    if (k)
		digitalWrite(DATA_II0, HIGH);
	    else
		digitalWrite(DATA_II0, LOW);
	} else if (i == 1) {	// GPIO17 Raspberry Pi Zero Pin 11
	    if (k)
		digitalWrite(DATA_II1, HIGH);
	    else
		digitalWrite(DATA_II1, LOW);
	} else if (i == 2) {
	    if (k)
		digitalWrite(DATA_II2, HIGH);
	    else
		digitalWrite(DATA_II2, LOW);
	} else if (i == 3) {
	    if (k)
		digitalWrite(DATA_II3, HIGH);
	    else
		digitalWrite(DATA_II3, LOW);
	} else if (i == 4) {
	    if (k)
		digitalWrite(DATA_II4, HIGH);
	    else
		digitalWrite(DATA_II4, LOW);
	} else if (i == 5) {
	    if (k)
		digitalWrite(DATA_II5, HIGH);
	    else
		digitalWrite(DATA_II5, LOW);
	} else if (i == 6) {
	    if (k)
		digitalWrite(DATA_II6, HIGH);
	    else
		digitalWrite(DATA_II6, LOW);
	} else if (i == 7) {
	    if (k)
		digitalWrite(DATA_II7, HIGH);
	    else
		digitalWrite(DATA_II7, LOW);
	}
    }

    S100_pSYNC();

    digitalWrite(MWRT, LOW);	// GPIO2 Raspberry Pi Zero Pin 3
    digitalWrite(sHLTA, LOW);	// GPIO3 Raspberry Pi Zero Pin 5                                        
    digitalWrite(sINTA, LOW);	// GPIO4 Raspberry Pi Zero Pin 7                                        
    digitalWrite(sWO, HIGH);	///// HIGH                      // GPIO5 Raspberry Pi Zero Pin 29 (Note output is invered by U23C)                                      
    digitalWrite(sM1, LOW);	// GPIO6 Raspberry Pi Zero Pin 31                       
    digitalWrite(sOUT, HIGH);	//// HIGH                       // GPIO7 Raspberry Pi Zero Pin 26
    digitalWrite(sINP, LOW);	// GPIO8 Raspberry Pi Zero Pin 24
    digitalWrite(sMEMR, LOW);	// GPIO9 Raspberry Pi Zero Pin 21

    digitalWrite(STATUS, HIGH);	// GPIO10 Raspberry Pi Zero Pin 19
    digitalWrite(STATUS, LOW);	// GPIO10 Raspberry Pi Zero Pin 19

    digitalWrite(WRITE_DATA, HIGH);	// GPIO13 Raspberry Pi Zero Pin 33

    digitalWrite(pSYNC, LOW);	// GPIO2 Raspberry Pi Zero Pin 3
    digitalWrite(pWR, LOW);	///// LOW                       // GPIO3 Raspberry Pi Zero Pin 5                                        
    digitalWrite(pSTVAL, HIGH);	// GPIO4 Raspberry Pi Zero Pin 7                                        
    digitalWrite(pDBIN, LOW);	// GPIO5 Raspberry Pi Zero Pin 29                                       
    digitalWrite(sXTRQ, HIGH);	// GPIO6 Raspberry Pi Zero Pin 31                       
    digitalWrite(CLEAR_INT, HIGH);	// GPIO7 Raspberry Pi Zero Pin 26

    digitalWrite(CTL, HIGH);	// GPIO0 Raspberry Pi Zero Pin 27
    digitalWrite(CTL, LOW);	// GPIO0 Raspberry Pi Zero Pin 27       

    digitalWrite(pSYNC, LOW);	// GPIO2 Raspberry Pi Zero Pin 3
    digitalWrite(pWR, HIGH);	///// HIGH                      // GPIO3 Raspberry Pi Zero Pin 5                                        
    digitalWrite(pSTVAL, HIGH);	// GPIO4 Raspberry Pi Zero Pin 7                                        
    digitalWrite(pDBIN, LOW);	// GPIO5 Raspberry Pi Zero Pin 29                                       
    digitalWrite(sXTRQ, HIGH);	// GPIO6 Raspberry Pi Zero Pin 31                       
    digitalWrite(CLEAR_INT, HIGH);	// GPIO7 Raspberry Pi Zero Pin 26

    digitalWrite(CTL, HIGH);	// GPIO0 Raspberry Pi Zero Pin 27
    digitalWrite(CTL, LOW);	// GPIO0 Raspberry Pi Zero Pin 27       

    digitalWrite(WRITE_DATA, LOW);	// GPIO13 Raspberry Pi Zero Pin 33
    EndBusCycle();

    pinMode(DATA_IO0, INPUT);	//Data Out or In  (Default INPUT)
    pinMode(DATA_IO1, INPUT);
    pinMode(DATA_IO2, INPUT);
    pinMode(DATA_IO3, INPUT);
    pinMode(DATA_IO4, INPUT);
    pinMode(DATA_IO5, INPUT);
    pinMode(DATA_IO6, INPUT);
    pinMode(DATA_IO7, INPUT);

//      printf("\nWritePort()");                                                // not sure why this is required
    return;
}

///////////////////////////////////////////// INTERRUPTS ///////////////////////////////////////////////////////////////


void IntSignalOn()
{
    Interrupts_Active = FALSE;
}


void IntSignalOff()
{
    Interrupts_Active = FALSE;
}


int CheckForInterrupts()	// If there was an interrupt process it
{
    int k = 0;
    if (!digitalRead(S100_INT))	// GPIO15 Raspberry Pi Zero Pin 10
    {
	Send_sINTA();
	k = ReadIntVector();
    }
    return k;			// Return 0 if no interrupt                                                             
}


void ClearInterrupts()		// Clear any pending interrupt
{
    EndBusCycle();
    digitalWrite(CLEAR_INT, LOW);	// GPIO7 Raspberry Pi Zero Pin 26
    digitalWrite(CTL, HIGH);	// GPIO0 Raspberry Pi Zero Pin 27
    digitalWrite(CTL, LOW);	// GPIO0 Raspberry Pi Zero Pin 27       
    digitalWrite(CLEAR_INT, HIGH);	// GPIO7 Raspberry Pi Zero Pin 26
    digitalWrite(CTL, LOW);	// GPIO0 Raspberry Pi Zero Pin 27       
}


void Send_sINTA()
{
    EndBusCycle();
    digitalWrite(sINTA, HIGH);	// GPIO4 Raspberry Pi Zero Pin 7                                        
    digitalWrite(STATUS, HIGH);	// GPIO0 Raspberry Pi Zero Pin 27
    digitalWrite(STATUS, LOW);	// GPIO0 Raspberry Pi Zero Pin 27
}

int ReadIntVector()
{
    int i, k;

    digitalWrite(pSYNC, LOW);	// GPIO2 Raspberry Pi Zero Pin 3
    digitalWrite(pWR, HIGH);	// GPIO3 Raspberry Pi Zero Pin 5                                        
    digitalWrite(pSTVAL, HIGH);	// GPIO4 Raspberry Pi Zero Pin 7                                        
    digitalWrite(pDBIN, HIGH);	///// HIGH                      // GPIO5 Raspberry Pi Zero Pin 29                                       
    digitalWrite(sXTRQ, HIGH);	// GPIO6 Raspberry Pi Zero Pin 31                       
    digitalWrite(CLEAR_INT, HIGH);	// GPIO7 Raspberry Pi Zero Pin 26

    digitalWrite(CTL, HIGH);	// GPIO0 Raspberry Pi Zero Pin 27
    digitalWrite(CTL, LOW);	// GPIO0 Raspberry Pi Zero Pin 27       

    digitalWrite(INPUT_INT, LOW);	///// LOW for U33               // GPIO14 Raspberry Pi Zero Pin 8

    for (i = 0; i < 8; i++)	// default direction of Pi data bits is to READ
    {
	if (i == 0) {
	    if (digitalRead(DATA_II0))	// GPIO16 Raspberry Pi Zero Pin 36
		k = 1;
	    else
		k = 0;
	} else if (i == 1) {	// GPIO17 Raspberry Pi Zero Pin 11
	    if (digitalRead(DATA_II1))
		k |= 0b00000010;
	} else if (i == 2) {
	    if (digitalRead(DATA_II2))	// GPIO18 Raspberry Pi Zero Pin 12
		k |= 0b00000100;
	} else if (i == 3) {
	    if (digitalRead(DATA_II3))	// GPIO19 Raspberry Pi Zero Pin 35
		k |= 0b00001000;
	} else if (i == 4) {
	    if (digitalRead(DATA_II4))	// GPIO20 Raspberry Pi Zero Pin 38
		k |= 0b00010000;
	} else if (i == 5) {
	    if (digitalRead(DATA_II5))	// GPIO21 Raspberry Pi Zero Pin 4
		k |= 0b00100000;
	} else if (i == 6) {
	    if (digitalRead(DATA_II6))	// GPIO22 Raspberry Pi Zero Pin 15
		k |= 0b01000000;
	} else if (i == 7) {
	    if (digitalRead(DATA_II7))	// GPIO23 Raspberry Pi Zero Pin 16
		k |= 0b10000000;
	}
    }
    digitalWrite(READ_DATA, LOW);	// GPIO13 Raspberry Pi Zero Pin 33
    EndBusCycle();
    return k;
}


void EndBusCycle()		// Clear all S100 Bus signals
{
    digitalWrite(READ_DATA, LOW);	// GPIO13 Raspberry Pi Zero Pin 33
    digitalWrite(WRITE_DATA, LOW);	// GPIO1 Raspberry Pi Zero Pin 28

    digitalWrite(MWRT, LOW);	// GPIO2 Raspberry Pi Zero Pin 3
    digitalWrite(sHLTA, LOW);	// GPIO3 Raspberry Pi Zero Pin 5                                        
    digitalWrite(sINTA, LOW);	// GPIO4 Raspberry Pi Zero Pin 7                                        
    digitalWrite(sWO, LOW);	// GPIO5 Raspberry Pi Zero Pin 29                                       
    digitalWrite(sM1, LOW);	// GPIO6 Raspberry Pi Zero Pin 31                       
    digitalWrite(sOUT, LOW);	// GPIO7 Raspberry Pi Zero Pin 26
    digitalWrite(sINP, LOW);	// GPIO8 Raspberry Pi Zero Pin 24
    digitalWrite(sMEMR, LOW);	// GPIO9 Raspberry Pi Zero Pin 21

    digitalWrite(STATUS, HIGH);	// GPIO10 Raspberry Pi Zero Pin 19
    digitalWrite(STATUS, LOW);	// GPIO10 Raspberry Pi Zero Pin 19

    digitalWrite(pSYNC, LOW);	// GPIO2 Raspberry Pi Zero Pin 3
    digitalWrite(pWR, HIGH);	// GPIO3 Raspberry Pi Zero Pin 5                                        
    digitalWrite(pSTVAL, HIGH);	// GPIO4 Raspberry Pi Zero Pin 7                                        
    digitalWrite(pDBIN, LOW);	// GPIO5 Raspberry Pi Zero Pin 29                                       
    digitalWrite(sXTRQ, HIGH);	// GPIO6 Raspberry Pi Zero Pin 31                       
    digitalWrite(CLEAR_INT, HIGH);	// GPIO7 Raspberry Pi Zero Pin 26

    digitalWrite(CTL, HIGH);	// GPIO0 Raspberry Pi Zero Pin 27
    digitalWrite(CTL, LOW);	// GPIO0 Raspberry Pi Zero Pin 27
    delay(1);
}



void S100_pSYNC()		// Pulse pSYNC high & (pSTVAL Low)
{
    digitalWrite(pSYNC, HIGH);	// GPIO2 Raspberry Pi Zero Pin 3
    digitalWrite(pWR, HIGH);	// GPIO3 Raspberry Pi Zero Pin 5                                        
    digitalWrite(pSTVAL, LOW);	// GPIO4 Raspberry Pi Zero Pin 7                                        
    digitalWrite(pDBIN, LOW);	// GPIO5 Raspberry Pi Zero Pin 29                                       
    digitalWrite(sXTRQ, HIGH);	// GPIO6 Raspberry Pi Zero Pin 31                       
    digitalWrite(CLEAR_INT, HIGH);	// GPIO7 Raspberry Pi Zero Pin 26

    digitalWrite(CTL, HIGH);	// GPIO0 Raspberry Pi Zero Pin 27
    digitalWrite(CTL, LOW);	// GPIO0 Raspberry Pi Zero Pin 27

    digitalWrite(pSYNC, LOW);	// GPIO2 Raspberry Pi Zero Pin 3
    digitalWrite(pWR, HIGH);	// GPIO3 Raspberry Pi Zero Pin 5                                        
    digitalWrite(pSTVAL, HIGH);	// GPIO4 Raspberry Pi Zero Pin 7                                        
    digitalWrite(pDBIN, LOW);	// GPIO5 Raspberry Pi Zero Pin 29                                       
    digitalWrite(sXTRQ, HIGH);	// GPIO6 Raspberry Pi Zero Pin 31                       
    digitalWrite(CLEAR_INT, HIGH);	// GPIO7 Raspberry Pi Zero Pin 26

    digitalWrite(CTL, HIGH);	// GPIO0 Raspberry Pi Zero Pin 27
    digitalWrite(CTL, LOW);	// GPIO0 Raspberry Pi Zero Pin 27
}
