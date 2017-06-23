.PHONY: all clean

# build java programs also in this Makefile
# because this project is just practice
.SUFFIXES: .java .class
.java.class:
	javac $<

targets = genrand min0 min1 \
	insertion_sort merge_sort heapsort \
	quick_sort rbtree knapsack_01

jtargets = RelabelToFront.class

CFLAGS = -Wno-implicit-function-declaration
CFLAGS += -Wno-main-return-type

all: $(targets) $(jtargets)
clean:
	rm -f util.o heap.o
	rm -f $(targets)
	rm -f *.class

genrand: genrand.c
min0: min0.c util.o
min1: min1.c util.o
insertion_sort: insertion_sort.c util.o
merge_sort: merge_sort.c util.o
heapsort: heapsort.c heap.o util.o

quick_sort: quick_sort.cc
rbtree: rbtree.cc
knapsack_01: knapsack_01.cc

# vim: set noet :
