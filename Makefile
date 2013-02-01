.PHONY: all clean

sources = genrand.c min0.c min1.c
objects = $(sources:.c=.o)
targets = $(objects:.o=)

all: $(targets)
clean:
	rm input.o
	rm $(objects) $(targets)

genrand: genrand.o
min0: min0.o input.o
min1: min1.o input.o

# vim: set noet :
