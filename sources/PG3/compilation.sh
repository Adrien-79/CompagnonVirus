echo 'Construction de MonPG3 ...'
gcc -Wall -o ../../executables/MonPG3 *.c -lm
echo 'MonPG3 : '.`readlink -f ../../executables/MonPG3`
