Mark-Sweep-GC
=============

This is an implementation of a simple Mark-Sweep garbage collector. I included two different mark routines. One of them is a classic DFS, using no additional memory. The other one, which was an idea of my own, uses a set of memory addresses to accelerate the computation, making it 100 times faster on average. The obvious disadvantage of this approach is that it isn't in-place, so it might not be appropiate for a standard GC.
