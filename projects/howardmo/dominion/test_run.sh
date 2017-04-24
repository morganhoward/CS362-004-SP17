#!/bin/bash
make dominion.o
make playdom
./playdom 10 > test10.txt
./playdom 11 > test11.txt
printf "\n**** Diff 10 Results ****\n"
diff output10.txt test10.txt
printf "\n**** Diff 11 Results ****\n"

