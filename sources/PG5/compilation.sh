echo 'Construction de SDL2'
cd ./sdl2_sources
./configure --disable-shared --prefix="$(pwd)/../sdl2_build"
make
make install
echo 'Construction de MonPG5 ...'
g++ -o ../../../executables/MonPG5 ../*.cc `../sdl2_build/bin/sdl2-config --static-libs`
echo 'MonPG5 : '.`readlink -f ../../executables/MonPG5`
