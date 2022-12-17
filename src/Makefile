CFLAGS = -DLINUX -g
CC = gcc

z80sim: z80sim.o util.o reg.o memory.o io.o debug.o
	$(CC) -g -o z80sim z80sim.o util.o reg.o memory.o io.o debug.o

z80sim.o: z80sim.c
	$(CC) $(CFLAGS) -c z80sim.c

clean:
	rm *.o
