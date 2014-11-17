#!/bin/bash
./net_sim 30 12 | tee results/30-12.txt
./net_sim 30 16 | tee results/30-16.txt
./net_sim 30 20 | tee results/30-20.txt
./net_sim 40 4 | tee results/40-4.txt
./net_sim 40 5 | tee results/40-5.txt
