#include "charArrayList.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define SIZE 100
#include <ctype.h>

CharList* CharList_constructor()
{
   CharList* temp = (CharList*)malloc(sizeof(CharList));

   temp->numelements = 0;
   temp->capacity = SIZE;
   temp->arr = (char**)malloc(sizeof(char**) * SIZE);

   return temp;
}

void add(CharList* l, char* name)
{
   int newsize;
   int index = l->numelements;
   int capacity = l->capacity;

   if(!isDotOrDotDot(name))
   {
      if(index == capacity - 1)
      {
         /* Double the size of the array */
         capacity = capacity * 2;
         newsize = capacity * sizeof(char*);
         l->arr = (char**)realloc(l->arr, newsize);
         if(l->arr == NULL)
         {
            perror("realloc");
            exit(-1);
         }
         l->capacity = capacity;
      }

      l->arr[index] = strdup(name);
      l->numelements++;
   }
}

void sort(CharList *cl)
{
   int i;
   int j;
   char* temp;
   char** lowest;
   int minIndex;
   int length = cl->numelements;
   /* char **newArr = (char**) malloc(sizeof(char**) * length); */

   for(i = 0; i < length; i++)
   {
      minIndex = i;
      lowest = &cl->arr[i];
      for(j = i + 1; j < length; j++)
      {
         if(strcasecmp(cl->arr[j], *lowest) < 0)
         {
            lowest = &cl->arr[j];
            minIndex = j;
         }
      }
      /* Swap */
      temp = cl->arr[i];
      cl->arr[i] = cl->arr[minIndex];
      cl->arr[minIndex] = temp;
   }
}
/*
int alphacmp(char* str1, char* str2)
{
   int strL1;
   int strL2;
   int loopLength;
   int i;
   char temp1;
   char temp2;

   if(str1 == NULL || str2 == NULL)
   {
      fprintf(stderr, "alphacmp: char* are null\n");
      exit(-1);
   }
   
   strL1 = strlen(str1);
   strL2 = strlen(str2);

   if(strL1 < strL2)
      loopLength = strL1;
   else
      loopLength = strL2;
   for(i = 0; i < loopLength; i++)
   {
      temp1 = str1[i];
      temp2 = str2[i];

      if(isalpha(temp1))
         temp1 = toupper(temp1);
      if(isalpha(temp2))
         temp2 = toupper(temp2);

      if(temp1 < temp2)
      {
         return -1;
      }
      if(temp2 < temp1)
      {
         return 1;
      }
   }

   return 0;
}
*/
CharList* delete(CharList* l)
{
   int i;

   for(i = 0; i < l->numelements; i++)
   {
      free(l->arr[i]);
   }

   free(l->arr);
   free(l);
   return NULL;
}

int isDotOrDotDot(char* name)
{
   if(name == NULL)
   {
      fprintf(stderr, "Char* is null");
      exit(-1);
   }

   if((strcmp(name, ".")) == 0)
      return 1;
   else if((strcmp(name, "..")) == 0)
      return 1;
   else
      return 0;
}
