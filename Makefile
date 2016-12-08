.PHONY: all clean

targets = genrand min0 min1 \
	insertion_sort merge_sort heapsort \
	quick_sort rbtree knapsack_01

CFLAGS = -Wno-implicit-function-declaration
CFLAGS += -Wno-main-return-type

all: $(targets)
clean:
	rm util.o heap.o
	rm $(targets)

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
