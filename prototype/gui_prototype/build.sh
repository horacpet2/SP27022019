#!/bin/sh



gcc main.c -o gui_prototype $(pkg-config --libs --cflags gtk+-3.0)
