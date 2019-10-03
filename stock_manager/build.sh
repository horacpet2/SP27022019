#!/bin/sh

MAIN="src/main.c"

OUTFILE="build/md_cash_desk"
CC="gcc "
LIBS="$(pkg-config --cflags --libs gtk+-3.0) -lm -L$(pg_config --libdir) -I$(pg_config --includedir) -lpq -L$HOME/lib/ -laclib -I$HOME/lib/include"
MODULES="$MAIN"


if [ $# -gt 0 ] && [ $1 = "-w" ]; then
	PARAMS="-Wall -g -std=gnu11 -I"C:/msys64/mingw64/x86_64-w64-mingw32/include" -L"C:/msys64/mingw64/x86_64-w64-mingw32/lib" -mwindows -lwinspool -o $OUTFILE.exe"
else
	PARAMS="-Wall -g -std=gnu11 -o $OUTFILE"
fi


clear 
$($CC $MODULES $PARAMS $LIBS)


# spustí přeložený program pouze pokud byl překlad bez chyb
if [ $? -eq 0 ]; then
	cd ./build

	if [ $# -gt 0 ] && [ $1 = "-w" ]; then
		./md_stock_manager.exe
	else
		./md_stock_manager
	fi

	cd ..
fi








