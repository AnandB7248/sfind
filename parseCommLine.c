#include "parseCommLine.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define NAME  1 
#define PRINT 2
#define EXEC  3
#define TRUE  1
#define FALSE 0

void parseCommLine(int argc, char* argv[], int* nameSptr, int* printSptr, int* execSptr, int* cmdIndex)
{
   int switchF;
   int index;

   /* Usage: sfind filename [-name str] -print | -exec ... \; */
   /* So at a minimum, 3 arguments must be given to follow proper usage convention. */
   if(argc < 3)
   {
      fprintf(stderr, "Usage: sfind filename [-name str] -print | -exec cmd ... \\;\n");
      fprintf(stderr, "Too few number of arguments: %d\n", argc);
      exit(-1);
   }

   /* Check if filename exists. (Can also be a path that leads to a directory, instead of a file) */
   if(access(argv[1], F_OK) == -1)
   {
      fprintf(stderr, "sfind: '%s': No such file or directory\n", argv[1]);
      exit(-1);
   }

   /* 3rd Command line guaranteed to be one of the switches */
   /* If not, give error and exit. */
   /* -name, -print, or -exec */
   if((switchF = isValidSwitch(argv[2])) == FALSE)
   {
      fprintf(stderr,"Usage: sfind filename (switch) \n");
      fprintf(stderr, "switch can be: -name, -print, -exec.\n");
      exit(-1);
   }
   /* switchF guaranteed to be 1,2,or 3 to represent the three valid switched */
   if(switchF == NAME) /* -name */
   {
      /* Command line argument after -name should be a string value that will represent a substring. */
      if(argc < 4)
      {
         fprintf(stderr, "Too few arguments: After -name, there needs to be a string value that represents a substring.\n");
         exit(-1);
      }
      /* If argument after -name is another switch, give error message and exit.*/
      if(isValidSwitch(argv[3]))
      {
         fprintf(stderr, "Usage: After -name, there needs to be a string value that represents a substring.\n");
         exit(-1);
      }
      /* Now at argv[4], it should be a switch. */
      /* sfind filename -name str (-print or -exec) */
      switchF = isValidSwitch(argv[4]);
      if((switchF != PRINT) && (switchF != EXEC))
      {
         fprintf(stderr, "Usage: sfind filename [-name str] -print | -exec cmd ... \\;\n");
         fprintf(stderr, "There should be a -print or -exec after -name str\n");
         exit(-1);
      }
      *nameSptr = TRUE; /* -name switch is set to true */

      /* Check if switch after -name str is either -print or -exec*/
      if(switchF == PRINT)
      { /* Currently: sfind filename -name str -print */
         if(argc != 5)
         {
            fprintf(stderr, "Usage: sfind filename [-name str] -print | -exec cmd ... \\;\n");
            fprintf(stderr, "-print detected. There should be no input after -print\n");
            exit(-1);
         }
         *printSptr = TRUE;
      }
      else if(switchF == EXEC)
      {
         /* This would mean command line arg is: sfind filename-name str -exec ... */
         /* Verify that number of arguments then is at least 7.*/
         /* The reason why 7 is because it is currently sfind filename -name str -exec, that is 5. */
         /* Then with exec there should be at least one command, that is 6 */
         /* And the command line argument then should end with ';' or \;, that is 7*/
         if(argc < 7)
         {
            fprintf(stderr, "Usage: sfind filename [-name str] -print | -exec cmd ... ;\n");
            fprintf(stderr, "Since -name is given and you wish to exec. Use at minumum: sfind filename -name str-exec (program to exec) ( \\; )\n");
            exit(-1);
         }
         /* Verify that since -exec is given, the command line argument ends with a \\; */
         if(strcmp(argv[argc - 1], ";") != 0)
         {
            fprintf(stderr, "Usage : sfind filename [-name str] -print | -exec cmd ... ;\n");
            exit(-1);
         }
         /* Verify that there is no switch given between command line arguments, -exec and \\; */
         /* Currently verified: sfind filename -name str -exec */
         /* Now at argv[3] */
         index = 5;
         while(index < (argc - 1))
         {
            if(isValidSwitch(argv[index++]))
            {
               fprintf(stderr, "Usage : sfind filename [-name str] -print | -exec cmd ... ;\n");
               fprintf(stderr, "Switch after -exec detected.\n");
               exit(-1);
            }
         }
         *cmdIndex = 5;
         *execSptr = 1;
      }
   }
   else if(switchF == PRINT) /* -print*/
   {  /* This would mean command line arg is: sfind filename -print.*/
      /* -name switch was not given */
      /* Verify number of command line arguments */
      /* There should only be 3: sfind filename -print, anymore would result in an error as it does not follow proper usage conventions. */
      if(argc != 3)
      {
         fprintf(stderr, "Usage: sfind filename [-name str] -print | exec cmd ... ;\n");
         fprintf(stderr, "Since -name is not given and you wish to print. Use: sfind filename -print\n");
         exit(-1);
      }
      *printSptr = 1;
   }
   else if(switchF == EXEC) /* -exec */
   {  /* This would mean command line arg is: sfind filename -exec ... */
      /* Verify that number of arguments then is at least 5.*/
      /* The reason why 5 is because it is currently sfind filename -exec, that is 3. */
      /* Then with exec there should be at least one command, that is 4 */
      /* And the command line argument then should end with ';' or \;, that is 5*/
      if(argc < 5)
      {
         fprintf(stderr, "Usage: sfind filename [-name str] -print | -exec cmd ... ;\n");
         fprintf(stderr, "Since -name is not given and you wish to exec. Use at the bare minimum: sfind filename -exec (program to exec) ( \\; )\n");
         exit(-1);
      }
      /* Verify that since -exec is given, the command line argument ends with a \\; */
      if(strcmp(argv[argc - 1], ";") != 0)
      {
         fprintf(stderr, "Usage : sfind filename [-name str] -print | -exec cmd ... ;\n");
         exit(-1);
      }
      /* Verify that there is no switch given between command line arguments, -exec and \\; */
      /* Currently verified: sfind filename -exec */
      /* Now at argv[3] */
      index = 3;
      while(index < (argc - 1))
      {
         if(isValidSwitch(argv[index++]))
         {
            fprintf(stderr, "Usage : sfind filename [-name str] -print | -exec cmd ... ;\n");
            fprintf(stderr, "Switch after -exec detected.\n");
            exit(-1);
         }
      }
      *cmdIndex = 3;
      *execSptr = 1;
      /* QUESTION: Is there any way to verify that the command given after -exec is a valid command? */
   }
}

int isValidSwitch(char* arg)
{
   if(arg == NULL)
   {
      fprintf(stderr, "In function isValidSwitch, %s is NULL.\n", arg);
      exit(-1);
   }
   if(strcmp(arg, "-name") == 0)
      return NAME;
   else if(strcmp(arg, "-print") == 0)
      return PRINT;
   else if(strcmp(arg, "-exec") == 0)
      return EXEC;
   else
      return FALSE;
}
