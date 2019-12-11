#!/bin/sh
set -e
cd ../sources
gcc main.c process.c -o main.exe
./main.exe