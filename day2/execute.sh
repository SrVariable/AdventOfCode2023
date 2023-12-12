#!/bin/bash

git submodule update --init --recursive
make -s -C ../BFL

gcc solver.c ../BFL/bfl.a -o solution
make fclean -C ../BFL

./solution input.txt
rm -f solution
