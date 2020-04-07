

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
int main()
{
	srand(time(NULL));
    
    int N = 0;
    printf("Programme approximation de PI (Methode Monte Carlo)\nSaisir le nombre de points : \n");

    scanf("%d", &N);
   

    FILE * temp = fopen("data.temp", "w");
  
    FILE * gnuplotPipe = popen ("gnuplot -persistent", "w");

    int inCercle = 0;

    for(int i = 0; i < N; i++){
    	double x = rand()/(RAND_MAX*1.0);
    	double y = rand()/(RAND_MAX*1.0);

    	int classe = (x*x + y*y) <= 1.0 ? 1 : 0; //Est ce que le point est dans le cercle ?

    	if(classe == 1){
    		inCercle++;   //Incremente le nombre de point dans le cercle
    	}

    	fprintf(temp, "%lf %lf %d\n", x, y, classe);  //On ecris notre point dans le fichier temp
	}

	double res = ((double) inCercle)/N *4.0; //On calcul pi 

	printf("Resultat : %lf\n", res);



    //OPTIONS GNUPLOT
	fprintf(gnuplotPipe, "set palette model RGB\n");
	fprintf(gnuplotPipe, "set palette model RGB defined (0 \"red\", 1 \"green\")\n");
    fprintf(gnuplotPipe, "set size square\n");
    fprintf(gnuplotPipe, "set parametric\n");
    fprintf(gnuplotPipe, "set xrange [0:1]\n");
	fprintf(gnuplotPipe, "set yrange [0:1]\n");

    //Affichage des points
	fprintf(gnuplotPipe, "plot 'data.temp' with points palette, [0:pi/2] sin(t),cos(t)\n");

    return 0;
}