echo 'Construction de MonPG4 ...'
gcc -Wall -Wno-misleading-indentation -o ../../executables/MonPG4 main.c -lm
echo 'MonPG4 : '.`readlink -f ../../executables/MonPG4`
