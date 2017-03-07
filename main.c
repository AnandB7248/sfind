#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "parseCommLine.h"
#include "checked.h"
#include "sfindUtil.h"

#define  TRUE 1
#define FALSE 0

int main(int argc, char* argv[])
{
   /* Command-line arguments usage: ./sfind filename [-name str] -print | -exec cmd ... \;*/

   int nameSwitch  = FALSE; 
   int printSwitch = FALSE; 
   int execSwitch  = FALSE;
   int cmdIndex;     /* cmdIndex is only given a value if -exec is given, holds the index cmd, of -exec cmd */
   int execArgc;     /* execArgc is only given a value if -exec is given, holds the number of arguments from cmd .... \; */
   char** cmdArgs;   /* cmdArgs  is only given a value if -exec is given, holds the original arguments from cmd ... \;*/
   char** execArgs;  /* execArgs is only given a value if -exec is given, holds the arguments to be given to execvp, 
                        if {} is detected, swaps it with the file/pathname */
   int origFD;       /* origFD is only given a value if -exec is given, holds the file descriptor of the original 
                        working directory where ./sfind was invoked*/

   /* Parse command line arguments, set the appropriate switchflags and save the the cmd argument index if -exec is given */
   parseCommLine(argc, argv, &nameSwitch, &printSwitch, &execSwitch, &cmdIndex);

   /* There is 4 possibilities with the switch combinations. */
   /* 1. Only -print */
   /* 2. Only -exec  */
   /* 3. -name and -print */
   /* 4. -name and exec */

   /* 1. Command-line is: sfind filename -print */
   if(nameSwitch == FALSE && printSwitch == TRUE && execSwitch == FALSE)
   {
      /* If filename is just a file */
      if(isFile(argv[1]))
         printf("%s\n", argv[1]);
      else
      {
         /* Change directory to argument filename, argv[1] */
         checked_chDir(argv[1]);
         sfind_print(argv[1]);
      }
   }

   /* 2. Command-line is: sfind filename -exec cmd ... \; */
   if(nameSwitch == FALSE && printSwitch == FALSE && execSwitch == TRUE)
   {
      cmdArgs = getCmdArgs(argc, argv, cmdIndex, &execArgc);

      /* If filename is just a file */
      if(isFile(argv[1]))
      {
         /* Set the command line arguments to exec, if {} detected, swap with the filename */
         execArgs = argsToExecCmd(cmdArgs, argv[1], execArgc);
         /* Exec cmd with the proper arguments */
         execCmd(execArgs);
         free(execArgs);
      }
      else
      {  /* Else, filename represents a path */
         /* Save a reference to the original working directory in the form of a fd */
         origFD = checked_open(".", O_RDONLY);
         /* Change directory to filename, path */
         checked_chDir(argv[1]);
         sfind_exec(argv[1], cmdArgs, execArgc, origFD);
         checked_close(origFD);
      }
      
      free(cmdArgs);
   }

   /* 3. Command-line is: sfind filename -name str -print */
   if(nameSwitch == TRUE && printSwitch == TRUE && execSwitch == FALSE)
   {
      /* If filename is a file, and str is a substring of the file's name */
      if(isFile(argv[1]))
      {
         if(isSubStr(argv[1], argv[3]))
            printf("%s\n", argv[1]);
      }
      else
      {
         /* Change directory to argument filename, argv[1] */
         checked_chDir(argv[1]);
         sfind_name_print(argv[1], argv[3]);
      }
   }

   /* 4. Command-line is: sfind filename -name str -exec cmd ... \; */
   if(nameSwitch == TRUE && printSwitch == FALSE && execSwitch == TRUE)
   {
      cmdArgs = getCmdArgs(argc, argv, cmdIndex, &execArgc);

      /* If filename is a file, and str is a substring of the file's name */
      if(isFile(argv[1]))
      {
         if(isSubStr(argv[1], argv[3]))
         {
            /* Set the command line arguments to exec, if {} detected, swap with the filename */
            execArgs = argsToExecCmd(cmdArgs, argv[1],execArgc);
            /* Exec cmd with the proper arguments */
            execCmd(execArgs);
            free(execArgs);
         }
      }
      else
      {
         /* Save a reference to the original working directory in the form of a fd */
         origFD = checked_open(".", O_RDONLY);
         /* Change directory to filename, path */
         checked_chDir(argv[1]);
         sfind_name_exec(argv[1], argv[3], cmdArgs, execArgc, origFD);
         checked_close(origFD);
      }

      free(cmdArgs);
   }

   return 0;
}
