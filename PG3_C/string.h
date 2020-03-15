
#ifndef STRING_H
#define STRING_H

typedef char* String;

void str_concat(String *dest, String source);
String str_new(String a);
void str_set(String *a, String b);
void str_delete(String s);
#endif
