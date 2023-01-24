CFLAGS = -DLINUX -g -DSTACKTRACE
CC = gcc

z80sim: z80sim.o util.o reg.o debug.o s100.o
	$(CC) -g -l wiringPi -o z80sim z80sim.o util.o reg.o debug.o s100.o

z80sim.o: z80sim.c
	$(CC) $(CFLAGS) -c z80sim.c

clean:
	rm *.o
