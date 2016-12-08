clrs
====

introduction to algorithm study

This is for studying algorithm.
No error will be cared much.
Thus, most function will be just 'void' func().
Written in C, array index starts from 0.

I am using Linux x86 32bit ubuntu 10.04
No other platform or architecture care

Algorithms
data structures 
some utilities

brief
=====

input*.txt
    sort input array
    (Ex)
    ./genrand 100000000 100000000 > A

genrand.c
    generate random numbers

min0.c
    Brute for loop minimum
    time ./min0 < A (1m29s)

min1.c
    Correct, but useless smart.
    Even slightly slower than min0
    time ./min1 < A (1m34s)

insertion_sort.c
merge_sort.c

heap.c
heapsort.c

quick_sort.cc

rbtree.cc

knapsack_01.cc
