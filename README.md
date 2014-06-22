Mark-Sweep-GC
=============

This is an implementation of a simple Mark-Sweep garbage collector. I included two different mark routines. One of them is a classic DFS, using no additional memory besides the one required by DFS' stack. The other one, which was an idea of my own, uses a set of memory addresses to accelerate the computation, making it 100 times faster on average. The obvious disadvantage of this approach is the usage of additional memory, so it might not be appropiate for a standard GC.

The program expects two folders to exist. To setup these folders run the config script. Then compile and build the program running make, which will place the binary file in the bin folder. The program usage information can be seen running

./bin/gc -h
