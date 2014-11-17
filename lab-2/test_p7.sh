#!/bin/bash
./net_sim 30 10 0.3 | tee results/30-10-03.txt
./net_sim 30 1 0.6 | tee results/30-1-06.txt
./net_sim 30 2 0.6 | tee results/30-2-06.txt
./net_sim 30 3 0.6 | tee results/30-3-06.txt
./net_sim 30 4 0.6 | tee results/30-4-06.txt
