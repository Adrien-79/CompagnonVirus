echo 'Construction de MonPG3 ...'
gcc -o ../../executables/MonPG3 *.c -lm
echo 'MonPG3 : '.`readlink -f ../../executables/MonPG3`
