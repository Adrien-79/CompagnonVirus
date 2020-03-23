

#include <stdlib.h>
#include <stdio.h>
#include <string.h> 


void addPoint(FILE* file, double (* tableau)[3]){
    double x = 0;
    double y = 0;
    double z = 0;

    fscanf(file, "%lf %lf %lf", &x, &y, &z);

    (*tableau)[0] = x;
    (*tableau)[1] = y;
    (*tableau)[2] = z;


}

void addShape(FILE * input, FILE * output,int MAX_POINTS ,double points[MAX_POINTS][3]){
    int pointA = 0;
    int pointB = 0;
    int pointC = 0;

    fscanf(input, "%d/%*d/%*d %d/%*d/%*d %d/%*d/%*d", &pointA, &pointB, &pointC);

    pointA--;
    pointB--;
    pointC--;

    fprintf(output, "%lf %lf %lf\n", points[pointA][0], points[pointA][1], points[pointA][2]);
    fprintf(output, "%lf %lf %lf\n", points[pointB][0], points[pointB][1], points[pointB][2]);
    fprintf(output, "\n");
    fprintf(output, "%lf %lf %lf\n", points[pointC][0], points[pointC][1], points[pointC][2]);
    fprintf(output, "%lf %lf %lf\n", points[pointA][0], points[pointA][1], points[pointA][2]);
    fprintf(output, "\n\n");

}

int main(int argc, char *argv[])
{


    int totalSurfaces = 0;

    char* surfaceAffichable;
    char* fichierName;

    if(argc != 3){
        printf("Erreur syntaxe : ./executable fichier.obj [1 ou 0 pour afficher les surfaces]\nExemple : ./executable sphere.obj 1\n" );
                exit(-1);
    }else{

        surfaceAffichable = argv[2];
        fichierName = argv[1];
    }

    int MAX_POINTS = 3000;
    double points[MAX_POINTS][3];
    int indexPoint = 0;

    //scanf("%d", &N);
   

    FILE * obj = fopen(fichierName, "r");
    if(obj == NULL){
        printf("Erreur, impossible d'ouvrir le fichier\n");
        exit(-1);
    }

    FILE * tempFile = fopen("data.temp", "w");



    char buff[255];
    while(fscanf(obj,"%s",buff) == 1){
     if(strcmp(buff, "v")==0){
        addPoint(obj, &(points[indexPoint++]));
       }
        else if(strcmp(buff, "f") == 0){
             //important pour multiples objets
            addShape(obj, tempFile,MAX_POINTS, points);
            totalSurfaces++;
        }
    }




    FILE * gnuplotPipe = popen ("gnuplot -persistent", "w");
    fprintf(gnuplotPipe, "unset log\n");
    fprintf(gnuplotPipe, "unset border\n");
    fprintf(gnuplotPipe, "set mouse\n");
    fprintf(gnuplotPipe, "set auto\n");

    if(strcmp(surfaceAffichable, "1") == 0){
        fprintf(gnuplotPipe, "set hidden3d\n");
    }

    fprintf(gnuplotPipe, "set style data lines\n");
    fprintf(gnuplotPipe, "set parametric\n");
    fprintf(gnuplotPipe, "splot 'data.temp' with lines\n" );
    fprintf(gnuplotPipe, "pause mouse keypress\n" );


    printf("Programme visualisation de fichiers OBJ (Triangles)\n");
    printf("Nombre de Points : %d\n", indexPoint);
    printf("Nombre de triangles : %d\n", totalSurfaces);


    
    return 0;
}