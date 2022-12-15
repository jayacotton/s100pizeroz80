/* s100 bus pin definitions */

/*
1       +8 V          51      +8V
2       +16 V         52      -16V
3       XRDY          53      GND
4       /VI0          54      /S CLR
5       /VI1          55      /DMA0
6       /VI2          56      /DMA1
7       /VI3          57      /DMA2
8       /VI4          58      /SXTRQ
9       /VI5          59      A19
10      /VI6          60      /SIXTN
11      /VI7          61      A20
12      /NMI          62      A21
13      /PWRFAIL      63      A22
14      /DMA3         64      A23
15      A18           65      ---
16      A16           66      ---
17      A17           67      /PHANTOM
18      /SDSB         68      MWRT
19      /CDSB         69      rsvd
20      GND           70      GND
21      ---           71      rsvd
22      /ADSB         72      RDY
23      /DODSB        73      /INT
24      phi2,phi0     74      /HOLD
25      /PSTVAL       75      /RESET
26      PHLDA         76      PSYNC
27      rsvd          77      /PWR
28      rsvd          78      PDBIN
29      A5            79      A0
30      A4            80      A1
31      A3            81      A2
32      A15           82      A6
33      A12           83      A7
34      A9            84      A8
35      DO1|D1        85      A13
36      DO0|D0        86      A14
37      A10           87      A11
38      DO4|D4        88      DO2|D2
39      DO5|D5        89      DO3|D3
40      DO6|D6        90      DO7|D7
41      DI2|D10       91      DI4|D12
42      DI3|D11       92      DI5|D13
43      DI7|D15       93      DI6|D14
44      SM1           94      DI1|D9
45      SOUT          95      DI0|D8
46      SINP          96      SINTA
47      SMEMR         97      /SWO
48      SHLTA         98      /ERROR
49      CLOCK         99      /POC
50      GND           100     GND
 */

#define XRDY          0
#define nVI0          0
#define nSCLR		0
#define nVI1         0		 
#define nDMA0	0
#define nVI2          	0
#define nDMA1	0
#define nVI3          	0
#define nDMA2	0
#define nVI4          	0
#define nSXTRQ	0
#define nVI5          	0
#define A19	0
#define nVI6          	0
#define nSIXTN	0
#define nVI7          	0
#define A20	0
#define nNMI          	0
#define A21	0
#define nPWRFAIL      	0
#define A22	0
#define nDMA3         	0
#define A23	0
#define A18           	0
#define A16           	0
#define A17           	0
#define nPHANTOM	0
#define nSDSB         	0
#define MWRT	0
#define nCDSB         	0
#define nADSB         	0
#define RDY	0
#define nDODSB        	0
#define nINT	0
#define phi2	0
#define phi0    	0
#define nHOLD	0
#define nPSTVAL       	0
#define nRESET	0
#define PHLDA         	0
#define PSYNC	0
#define nPWR	0
#define PDBIN	0
#define A5            	0
#define A0	0
#define A4            	0
#define A1	0
#define A3            	0
#define A2	0
#define A15           	0
#define A6	0
#define A12           	0
#define A7	0
#define A9            	0
#define A8	0
#define DO1orD1        	0
#define A13	0
#define DO0orD0        	0
#define A14	0
#define A10           	0
#define A11	0
#define DO4orD4        	0
#define DO2orD2	0
#define DO5orD5        	0
#define DO3orD3	0
#define DO6orD6        	0
#define DO7orD7	0
#define DI2orD10       	0
#define DI4orD12	0
#define DI3orD11       	0
#define DI5orD13	0
#define DI7orD15       	0
#define DI6orD14	0
#define SM1           	0
#define DI1orD9	0
#define SOUT          	0
#define DI0orD8	0
#define SINP          	0
#define SINTA	0
#define SMEMR         	0
#define nSWO	0
#define SHLTA         	0
#define nERROR	0
#define CLOCK         	0
#define nPOC	0
