CFLAGS=-Wall -g

all:
	ex19

ex19: object.o

test: test.bash

.PHONY: clean
clean:
	-rm -f ex19
	-rm -f object.o
	-rm -f test.bash
