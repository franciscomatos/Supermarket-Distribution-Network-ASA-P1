# Supermarket Distribution Network

This project consists on a program written in C++ which purpose is to find the regional sub-networks of a supermarket chain in order to be possible for any distribution point in a region to send products to any other point in the same region. I implemented Tarjan's Algorithm to solve this problem.

## Getting Started

You will need the g++ compiler installed in your machine.

### Compiling

Download the .zip and compile the 'main.cpp' file using the following command:

```
$ g++ -o supermarket main.cpp
```
which should create the executable file 'supermarket'.

## Running

Make sure the executable file is in the same directory as the input files contained in 'tests'.
The program should be executed in the following way:

```
$ ./supermarket < st01.in > test01.myout
```

Afterwards you can compare your output with the foressen output using:

```
$ diff st01.out test01.myout
```

## Author

* Francisco Matos

## Evaluation

18/20
