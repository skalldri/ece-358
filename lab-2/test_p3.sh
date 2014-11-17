#!/bin/bash
./net_sim 30 10 0.01 | tee results/30-10-001.txt
./net_sim 30 1 0.1 | tee results/30-1-01.txt
./net_sim 30 2 0.1 | tee results/30-2-01.txt
./net_sim 30 3 0.1 | tee results/30-3-01.txt
./net_sim 30 4 0.1 | tee results/30-4-01.txt
