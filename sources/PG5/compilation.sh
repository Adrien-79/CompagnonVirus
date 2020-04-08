#!/bin/bash
cd sdl2_sources
DIR="../sdl2_build"
if [ ! -d "$DIR" ];
then
	echo 'Construction de SDL2'
	./configure --disable-shared --prefix="$(pwd)/../sdl2_build"
	make
	make install
fi

echo 'Construction de MonPG5 ...'
g++ -o ../../../executables/MonPG5 ../*.cc `../sdl2_build/bin/sdl2-config --static-libs`
echo 'MonPG5 : '.`readlink -f ../../executables/MonPG5`
