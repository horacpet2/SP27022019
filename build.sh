#!/bin/sh



OUTFILE="build/md_cash_desk"
CC="gcc -Wall -g -std=gnu11 -o $OUTFILE"

MAIN="src/main.c"


LIBS="$(pkg-config --cflags --libs gtk+-3.0) -lm"
MODULES="$MAIN"





$($CC $MODULES $LIBS)







