#ifndef SFINDUTIL_H
#define SFINDUTIL_H
#include "charArrayList.h"

/* Function that will execute sfind when command-line arguments is: sfind filename -print */
/* Paramters: string - char* that represents filename, which is the starting point where we will recursively process all the files in the hierarchy */
void sfind_print(char*);

/* Function that will execute sfind when command-line argument is: sfind filename -name str -print*/
/* Parameters: (first parameter) string- char* that reprents filename, which is the starting point where we will recursively process all the files in the hierarchy */
/*             (second parameter) string-char* that represents the substring to find */
void sfind_name_print(char*, char*);

/* ------------------------------------------------------*/
/* ---------------------HELPER METHODS ------------------*/
/* ------------------------------------------------------*/

/* Boolean function that returns true or false depending on if the char* argument given is a file or not */
int isFile(char*);

int isDir(char*);

/* Boolean function that returns true or false depending on if the file argument referenced by char*'s exec bit is set */
int isExecSet(char*);

/* Boolean function that returns true or false depending on if the char*-needle is in the char*-haystack or not */
int isSubStr(const char* haystack, const char* needle);

/* Obtains the contents of the current directory */
/* and places it in sorted order to address specified by CharList */
void sortFiles(CharList**);

void dynamicStrCat(char**, char*, const char*, char*);

void checked_chDir(char*);

#endif
