#ifndef PARSECOMMLINE_H
#define PARSECOMMLINE_H

/* Parses the command line arguments to sfind */
/* Command Line usage-example: sfind filename [-name str] -print | exec cmd ;*/
/* [-name str] is optional */
/* Either -print or -exec flag will be used, not both */
/* -------------------------------------------------- */
/* Pre-conditions: valid command line arguments which follow usage */
/* Postconditions: Ensures that the user has followed proper command line argument usage*/
/*                 -name -print -exec switches will be set. True/False*/
/*                 If -exec was given, index of command will be set */
void parseCommLine(int, char**, int*, int*, int*,int*);

/* Takes the string argument and tests if it is a valid switch */
/* Valid switch is -name, -print, -exec */
/* Pre-conditions: none */
/* Postconditions: Returns 0, if argument is not one of the switches*/
/*                 Returns 1, if -name  */
/*                 Returns 2, if -print */
/*                 Returns 3, if -exec  */
int isValidSwitch(char*);

#endif
