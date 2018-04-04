.PHONY: all clean

all:
	cd lib/src && make
	cd src && make

clean:
	cd lib/src && make clean
	cd src && make clean
	rm -f bin/*
	
