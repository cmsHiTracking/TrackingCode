#!/bin/sh

cat out.txt | grep "Total job" | awk '{print $4}' >CPUratio.txt

grep TimeModule\> out.txt > TimingInfo.txt

g++ timing.cpp -o timing.out

./timing.out >TimingModule.txt


