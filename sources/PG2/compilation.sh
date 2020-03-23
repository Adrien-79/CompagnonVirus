echo 'Construction de MonPG2 ...'
gcc -o ../../executables/MonPG1 MonPG2.c
echo 'MonPG2 : '.`readlink -f ../../executables/MonPG2`
