#!/bin/sh

cat PbPbstep3.txt | grep "Total job" | awk '{print $4}' >CPUratio.txt

grep TimeModule\> PbPbstep3.txt > TimingInfo.txt

g++ timing.cpp -o timing.out

./timing.out >TimingModule.txt

