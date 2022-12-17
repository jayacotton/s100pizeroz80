/* interface from cpu code to s100 memory h/w */
/* the write ram module can only be used on the pi zero board.  For
testing on linux its not going to interface with h/w */

#ifndef LINUX
unsigned int addrbits[] = {
    DATA_A0, DATA_A1, DATA_A2, DATA_A3, DATA_A4, DATA_A5, DATA_A6, DATA_A7,
    DATA_A8,
    DATA_A9, DATA_A10, DATA_A11, DATA_A12, DATA_A10, DATA_A10, DATA_A13,
    DATA_A14, DATA_A15,
    DATA_A16, DATA_A17, DATA_A18, DATA_A19, DATA_A20, DATA_A21, DATA_A22,
    DATA_A23
};

unsigned int databits[] = {
    DATA_II0, DATA_II1, DATA_II2, DATA_II3, DATA_II4, DATA_II5, DATA_II6,
    DATA_II7
};

SetAddressReg(int location)
{
    int i;
    int k = 0;
    for (i = 0; i < 24; i++) {
	k = ((location >> i) & 1);
	digitalWrite(addrbits[i], k ? HIGH : LOW);
	if (i == 7) {
	    digitalWrite(ADD_LOW, HIGH);	//Latch low address lines
	    digitalWrite(ADD_LOW, LOW);
	} else if (i == 15) {
	    digitalWrite(ADD_HIGH, HIGH);	//Latch high address lines
	    digitalWrite(ADD_HIGH, LOW);
	} else if (i == 23) {
	    digitalWrite(ADD_EXT, HIGH);	//Latch extended address lines
	    digitalWrite(ADD_EXT, LOW);
	}
    }
}
#endif

#ifdef LINUX
void WriteRAM(int location, int value)
{				/* no idea what I will do here yet */
}

char ReadRAM(int location)	// Set S100 bus address lines A0-A23 to a value (24 bits wide)
{
}
#else
void WriteRAM(int location, int value)	// Set S100 bus address lines A0-A23 to a value (24 bits wide)
{				// Remember location is a long
    int i;
    int k = 0;

    SetAddressReg(location);

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
	digitalWrite(databits[i], k ? HIGH : LOW);
    }


    S100_pSYNC();

    digitalWrite(MWRT, HIGH);	//HIGH     // GPIO2 Raspberry Pi Zero Pin 3
    digitalWrite(MWRT, HIGH);	//HIGH     // GPIO2 Raspberry Pi Zero Pin 3
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
    digitalWrite(pWR, LOW);	//LOW   // GPIO3 Raspberry Pi Zero Pin 5                                        
    digitalWrite(pWR, LOW);	//LOW   // GPIO3 Raspberry Pi Zero Pin 5                                        
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

char ReadRAM(int location)	// Set S100 bus address lines A0-A23 to a value (24 bits wide)
{				// Remember location is a int
    int i;
    int k = 0;

    SetAddressReg(location);

    S100_pSYNC();

    digitalWrite(MWRT, LOW);	// GPIO2 Raspberry Pi Zero Pin 3
    digitalWrite(sHLTA, LOW);	// GPIO3 Raspberry Pi Zero Pin 5                                        
    digitalWrite(sINTA, LOW);	// GPIO4 Raspberry Pi Zero Pin 7                                        
    digitalWrite(sWO, LOW);	// GPIO5 Raspberry Pi Zero Pin 29                                       
    digitalWrite(sM1, LOW);	// GPIO6 Raspberry Pi Zero Pin 31                       
    digitalWrite(sOUT, LOW);	// GPIO7 Raspberry Pi Zero Pin 26
    digitalWrite(sINP, LOW);	// GPIO8 Raspberry Pi Zero Pin 24
    digitalWrite(sMEMR, HIGH);	//HIGH  // GPIO9 Raspberry Pi Zero Pin 21
    digitalWrite(sMEMR, HIGH);	//HIGH  // GPIO9 Raspberry Pi Zero Pin 21

    digitalWrite(STATUS, HIGH);	// GPIO10 Raspberry Pi Zero Pin 19
    digitalWrite(STATUS, LOW);	// GPIO10 Raspberry Pi Zero Pin 19

    digitalWrite(READ_DATA, HIGH);	// GPIO13 Raspberry Pi Zero Pin 33

    digitalWrite(pSYNC, LOW);	// GPIO2 Raspberry Pi Zero Pin 3
    digitalWrite(pWR, HIGH);	// GPIO3 Raspberry Pi Zero Pin 5                                        
    digitalWrite(pSTVAL, HIGH);	// GPIO4 Raspberry Pi Zero Pin 7                                        
    digitalWrite(pDBIN, HIGH);	//HIGH  // GPIO5 Raspberry Pi Zero Pin 29                                       
    digitalWrite(pDBIN, HIGH);	//HIGH  // GPIO5 Raspberry Pi Zero Pin 29                                       
    digitalWrite(sXTRQ, HIGH);	// GPIO6 Raspberry Pi Zero Pin 31                       
    digitalWrite(CLEAR_INT, HIGH);	// GPIO7 Raspberry Pi Zero Pin 26

    digitalWrite(CTL, HIGH);	// GPIO0 Raspberry Pi Zero Pin 27
    digitalWrite(CTL, LOW);	// GPIO0 Raspberry Pi Zero Pin 27       


    for (i = 0; i < 8; i++)	// bits to READ already set
    {
	k |= (digitalRead(databits[i]) ? 1 << i | 0);
    }
    digitalWrite(READ_DATA, LOW);	// GPIO13 Raspberry Pi Zero Pin 33
    EndBusCycle();
    return (char) k;
}
#endif
