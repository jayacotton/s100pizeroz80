#define RUN_BASE 0xe000

typedef struct OpCodes{
unsigned int Val;
char *code1;
char *code2;
char *code3;
char *code4;
char *code5;
} OPCODES;

extern unsigned short PCAddress;
extern unsigned short StackPointer;

extern unsigned char Areg;
extern unsigned char Breg;
extern unsigned char Creg;
extern unsigned char Dreg;
extern unsigned char Ereg;
extern unsigned char Hreg;
extern unsigned char Lreg;

/* alternate register set */
extern unsigned char Areg_;
extern unsigned char Breg_;
extern unsigned char Creg_;
extern unsigned char Dreg_;
extern unsigned char Ereg_;
extern unsigned char Hreg_;
extern unsigned char Lreg_;

extern unsigned int IXreg;
extern unsigned int IYreg;

extern unsigned char CpuStatus;
extern unsigned char CpuStatus_;
#define SFlag 0x80
#define ZFlag 0x40
#define HFlag 0x10
#define PFFlag 0x4
#define NFlag 0x2
#define CFlag 0x1

extern unsigned char Ireg;
extern unsigned char IntState;
