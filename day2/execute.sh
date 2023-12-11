#!/bin/bash

git submodule update --init --recursive
make -s -C BFL
make -s -C get_next_line

gcc solver.c BFL/bfl.a get_next_line/gnl.a -o solution
make fclean -s -C BFL
make fclean -s -C get_next_line

./solution input.txt
rm -f solution
