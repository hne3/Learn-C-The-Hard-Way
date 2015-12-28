CFLAGS=-Wall -g

all:
	ex19

ex19: object.o

.PHONY: clean
clean:
	-rm -f ex19
