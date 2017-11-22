#!/bin/bash
mkdir -p build
gcc src/billing-timer.c -o build/billing-timer -lncurses
chmod +x build/billing-timer
