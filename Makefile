CFLAGS=-Wall -g -DNDEBUG

all:
	ex22_main

ex22.o: ex22.h ex22.c

ex22_main: ex22_main.c ex22.o 

.PHONY: clean
clean:
	-rm -f ex22_main
	-rm -f ex22.o
