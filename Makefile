.PHONY: all clean

sources = genrand.c min0.c min1.c \
	insertion_sort.c merge_sort.c
objects = $(sources:.c=.o)
targets = $(objects:.o=)

all: $(targets)
clean:
	rm util.o
	rm $(objects) $(targets)

genrand: genrand.o
min0: min0.o util.o
min1: min1.o util.o
insertion_sort: insertion_sort.o util.o
merge_sort: merge_sort.o util.o

# vim: set noet :
