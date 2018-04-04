IPCPATH = ../lib 
CFLAGS = -Wall -I$(IPCPATH) -g -O3

all: BrainMachine

BrainMachine: BrainMachine.o
	gcc -o ../brain BrainMachine.o -L$(IPCPATH) -lB

BrainMachine.o: BrainMachine.c
	gcc -c $(CFLAGS) BrainMachine.c

.PHONY: all clean

clean:
	rm -f ../brain BrainMachine.o