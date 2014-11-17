#!/bin/bash
./net_sim 30 10 0.1 | tee results/30-10-01.txt
./net_sim 30 1 0.3 | tee results/30-1-03.txt
./net_sim 30 2 0.3 | tee results/30-2-03.txt
./net_sim 30 3 0.3 | tee results/30-3-03.txt
./net_sim 30 4 0.3 | tee results/30-4-03.txt
