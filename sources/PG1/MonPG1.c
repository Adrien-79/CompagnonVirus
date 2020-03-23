

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

    	int classe = (x*x + y*y) <= 1.0 ? 1 : 0;

    	if(classe == 1){
    		inCercle++;// = inCercle + 1;
    	}

    	fprintf(temp, "%lf %lf %d\n", x, y, classe); //Write the data to a temporary fil
	}

	double res = ((double) inCercle)/N *4.0;

	printf("Resultat : %lf\n", res);



	fprintf(gnuplotPipe, "set palette model RGB\n");
	fprintf(gnuplotPipe, "set palette model RGB defined (0 \"red\", 1 \"green\")\n");
    fprintf(gnuplotPipe, "set size square\n");
    fprintf(gnuplotPipe, "set parametric\n");
    fprintf(gnuplotPipe, "set xrange [0:1]\n");
	fprintf(gnuplotPipe, "set yrange [0:1]\n");


	fprintf(gnuplotPipe, "plot 'data.temp' with points palette, [0:pi/2] sin(t),cos(t)\n");
			//fprintf(gnuplotPipe, "\n");


    return 0;
}