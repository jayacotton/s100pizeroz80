/* interface from z80 simulator to s100 bus i/o h/w */

#ifndef LINUX
char ReadPort(int location)	// Set S100 bus address lines A0-A15 to a value (24 bits wide)
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
		k |= 0 b00000010;
	} else if (i == 2) {
	    if (digitalRead(DATA_II2))	// GPIO18 Raspberry Pi Zero Pin 12
		k |= 0 b00000100;
	} else if (i == 3) {
	    if (digitalRead(DATA_II3))	// GPIO19 Raspberry Pi Zero Pin 35
		k |= 0 b00001000;
	} else if (i == 4) {
	    if (digitalRead(DATA_II4))	// GPIO20 Raspberry Pi Zero Pin 38
		k |= 0 b00010000;
	} else if (i == 5) {
	    if (digitalRead(DATA_II5))	// GPIO21 Raspberry Pi Zero Pin 4
		k |= 0 b00100000;
	} else if (i == 6) {
	    if (digitalRead(DATA_II6))	// GPIO22 Raspberry Pi Zero Pin 15
		k |= 0 b01000000;
	} else if (i == 7) {
	    if (digitalRead(DATA_II7))	// GPIO23 Raspberry Pi Zero Pin 16
		k |= 0 b10000000;
	}
    }
    digitalWrite(READ_DATA, LOW);	// GPIO13 Raspberry Pi Zero Pin 33
    EndBusCycle();
//      printf("\nReadPort()");                                                 // not sure why this is required
    return k;
}


void WritePort(int location, int value)	// Set S100 bus address lines A0-A15 to a value (24 bits wide)
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
#endif
