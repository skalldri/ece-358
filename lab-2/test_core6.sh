#!/bin/bash
./net_sim 80 6 | tee results/80-6.txt
./net_sim 80 7 | tee results/80-7.txt
./net_sim 100 5 | tee results/100-5.txt
./net_sim 100 6 | tee results/100-6.txt
./net_sim 100 7 | tee results/100-7.txt
