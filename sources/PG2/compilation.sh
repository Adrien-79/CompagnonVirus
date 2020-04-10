echo 'Construction de MonPG2 ...'
gcc -Wall -o ../../executables/MonPG2 MonPG2.c
echo 'MonPG2 : '.`readlink -f ../../executables/MonPG2`
