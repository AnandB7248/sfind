#ifndef CHARARRAYLIST_H
#define CHARARRAYLIST_H

typedef struct{
   char** arr;
   int numelements;
   int capacity;
} CharList;

CharList* CharList_constructor();
void add(CharList*, char*);
CharList* delete(CharList*);
void sort(CharList*);
int alphacmp(char*, char*);
int isDotOrDotDot(char*);
#endif
