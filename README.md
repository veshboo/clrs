clrs
====

introduction to algorithm study

This is for studying algorithm.
No error will be cared much.
Thus, most function will be just 'void' func().

I'm using Linux x86 32bit ubuntu 10.04
No other platform or architecture care

brief
=====

input*.txt  : sort input array
              (Ex)
              ./genrand 100000000 100000000 > A

genrand.c   : generate random numbers

min0.c      : Brute for loop minimum
              time ./min0 < A (1m29s)

min1.c      : Correct, but useless smart.
              Even slightly slower than min0
              time ./min1 < A (1m34s)
