#!/bin/sh

MAIN="src/main.c"

OUTFILE="build/md_cash_desk"
CC="gcc "
LIBS="$(pkg-config --cflags --libs gtk+-3.0) -lm"
MODULES="$MAIN"


if [ $# -gt 0 ] && [ $1 = "-w" ]; then
	PARAMS="-Wall -g -std=gnu11 -mwindows -o $OUTFILE"
else
	PARAMS="-Wall -g -std=gnu11 -o $OUTFILE"
fi


clear 
$($CC $PARAMS $MODULES $LIBS)


# spustí přeložený program pouze pokud byl překlad bez chyb
if [ $? -eq 0 ]; then
	cd ./build

	if [ $# -gt 0 ] && [ $1 = "-w" ]; then
		./md_cash_desk.exe
	else
		./md_cash_desk
	fi

	cd ..
fi








