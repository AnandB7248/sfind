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

void sfind_exec(char*, char**, char*, int);

void sfind_name_exec(char*,char*, char**, char*, int);

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

/* This function is used when -exec is present in the command-line. */
/* Function returns the number of braces between -exec and \; */
int bracesExist(int, char**, int);
/* Obtains the contents of the current directory */
/* and places it in sorted order to address specified by CharList */
void sortFiles(CharList**);

void dynamicStrCat(char**, char*, const char*, char*);

void checked_chDir(char*);

char** argsToExecCmd(char**, char*, char*, int);

char** getCmdArgs(int, char**, int, int*);

/* char* cmd to execute */
/* char** argv equivalent to the cmd to be executed.*/
void execCmd(char**);

#endif
