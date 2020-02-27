#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TEXT_SIZE 10
#define LINE_SIZE 10

int main(int argc, char ** argv)
{
    if(argc <= 1)
    {
        printf("Usage: %s text\n", argv[0]);
        return 0;
    }

   /* char text[MAX_TEXT_SIZE] = "";
    int totalSize = 0;
    for(int i = 1; i < argc; i++)
    {
        totalSize += strlen(argv[i]);
        char * toCopy = argv[i];
        if(totalSize +1> MAX_TEXT_SIZE)
        {
            int N = MAX_TEXT_SIZE - strlen(text);//totalSize + strlen(argv[i])+1;
            char * rest = malloc(N*sizeof(char));
            strncpy(rest,toCopy,N-1);
            rest[N-1] = 0; //Null char
            strcat(text,rest);
            free(rest);
            rest = NULL;
            break;
        }
        strcat(text,toCopy);
    }*/

    char * text = malloc((strlen(argv[1])+1)*sizeof(char));
    strcpy(text,argv[1]);

    printf("Text: %s\n",text);

    int nbLines = strlen(text) / LINE_SIZE; //TODO manage last line
    char dst[LINE_SIZE+1] = "";
    for(int i = 0; i < nbLines; i++)
    {
        int start = i*LINE_SIZE;
        strncpy(dst,text + start,LINE_SIZE);
        printf("%s\n",dst);
    }
    

    free(text);
    text = NULL;
}