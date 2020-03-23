echo 'Suppression des fichiers...'
rm ./executables/MonPG*
rm ./executables/MediaPlayer.exe

printf "\nCompilations...\n"
cd ./sources/MediaPlayer/
./compilation.sh
printf "\n"
cd ../PG1/
./compilation.sh
printf "\n"
cd ../PG2/
./compilation.sh
printf "\n"
cd ../PG3/
./compilation.sh
printf "\n\n\nSortie : ./executables/\n Fin du nettoyage des fichiers\n"
