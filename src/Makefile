;CFLAGS = -g -DLINUX -DNEVER -O3 
;CFLAGS = -DLINUX -DNEVER -DLOCALRAM -O3 
CFLAGS = -DLINUX -DNEVER -DPERFCHECK -O3 
;CFLAGS = -g -O3 -DNEVER -DLINUX -DSTACKTRACE -DBREAK -DTRACEF 
CC = gcc

z80sim: z80sim.o util.o reg.o debug.o s100.o sim1.o simglb.o sim2.o sim3.o sim4.o sim5.o sim7.o sim6.o simfun.o
	$(CC) -g -l wiringPi -o z80sim z80sim.o reg.o debug.o s100.o sim1.o simglb.o sim2.o sim3.o sim4.o sim5.o sim7.o sim6.o util.o simfun.o

z80sim.o: z80sim.c
	$(CC) $(CFLAGS) -c z80sim.c

clean:
	rm *.o
