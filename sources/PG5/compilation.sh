#!/bin/bash

echo 'Construction de MonPG5 ...'
g++ -Wall -o ../../executables/MonPG5  *.cc `sdl2-config --cflags --libs`
echo 'MonPG5 : '.`readlink -f ../../executables/MonPG5`
