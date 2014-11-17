#!/bin/bash
./net_sim 20 12 | tee results/20-12.txt
./net_sim 20 16 | tee results/20-16.txt
./net_sim 20 20 | tee results/20-20.txt
./net_sim 30 4 | tee results/30-4.txt
./net_sim 30 8 | tee results/30-8.txt
