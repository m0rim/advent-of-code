#!/bin/bash
g++ -std=c++17 -O3 main.cpp
time ./a.out < input
rm -f a.out
