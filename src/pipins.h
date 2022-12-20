/* copied from Johns PI code */

/* this is how the pi is connected to the s100 bus */
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
#define CONSOLE_FLAG 14		// GPIO14 Determines if Console input is S100 bus or Raspberry)
