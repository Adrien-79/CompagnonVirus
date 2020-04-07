echo 'Construction de MonPG4 ...'
gcc -o ../../executables/MonPG4 main.c -lm
echo 'MonPG4 : '.`readlink -f ../../executables/MonPG4`
