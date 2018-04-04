INCDIR    =  -iquote 
COMPILER = gcc
CFLAGS =$(INCDIR) -Wall -g -O3
REP = ../
LIBRAIRIE = $(REP)/libB.a
 
CFILES    = tools.c parser.c machineStruct.c machine.c
OFILES    = $(CFILES:.c=.o) 

all: $(LIBRAIRIE)

$(LIBRAIRIE) : $(OFILES)
	@echo "Building $@ ... "
	ar r $@ $(OFILES); ranlib $@
	@echo "$@ done"


.c.o:
	$(COMPILER) $(CFLAGS) -c $*.c


.PHONY: all clean

clean:
	rm -f $(OFILES) $(LIBRAIRIE) core