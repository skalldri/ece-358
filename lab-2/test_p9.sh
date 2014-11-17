#!/bin/bash
./net_sim 30 10 0.6 | tee results/30-10-06.txt
./net_sim 30 1 1.1 | tee results/30-1-1.txt
./net_sim 30 2 1.1 | tee results/30-2-1.txt
./net_sim 30 3 1.1 | tee results/30-3-1.txt
./net_sim 30 4 1.1 | tee results/30-4-1.txt
