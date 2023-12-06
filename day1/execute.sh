#!/bin/bash

make re -C BFL
make re -C get_next_line

gcc solver.c BFL/bfl.a get_next_line/gnl.a -o solution
make fclean -C BFL
make fclean -C get_next_line

./solution input.txt
rm -f solution
