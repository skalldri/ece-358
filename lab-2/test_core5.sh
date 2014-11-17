#!/bin/bash
./net_sim 40 20 | tee results/40-20.txt
./net_sim 60 5 | tee results/60-5.txt
./net_sim 60 6 | tee results/60-6.txt
./net_sim 60 7 | tee results/60-7.txt
./net_sim 80 5 | tee results/80-5.txt
