#include <stdlib.h>
#include <string.h>
#include "string.h"



String str_new(String a){
	String s;
	s = (char *)malloc(sizeof(char) * (strlen(a) + 1));
	strcpy(s, a);
	return s;
}

void str_set(String *a, String b){
	free( *a);
	*a = (char*) malloc((strlen(*a) + 1)*sizeof(char));
	strcpy(*a, b);
}

void str_concat(String* dest, String source){
	String strTemp = (char*) malloc((strlen(*dest) + strlen(source) + 1)*sizeof(char));
	strcpy(strTemp, *dest);
	strcat(strTemp, source);
	free(*dest);
	*dest = strTemp;
}


void str_delete(String s){
	free(s);
}
