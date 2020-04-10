echo 'Construction de MediaPlayer ...'
gcc -Wall `pkg-config --cflags gtk+-3.0` -o ../../executables/MediaPlayer.exe ImageViewer.c `pkg-config --libs gtk+-3.0`
cp -r glade_ui ../../executables/glade_ui
echo 'MediaPlayer : '.`readlink -f ../../executables/MediaPlayer.exe`
