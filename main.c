#include <stdio.h>
#include <stdlib.h>
#include "parseCommLine.h"
#include "sfindUtil.h"

#define  TRUE 1
#define FALSE 0

int main(int argc, char* argv[])
{
   /* Set all switches to false initially */
   int nameSwitch  = FALSE;
   int printSwitch = FALSE;
   int execSwitch  = FALSE;
   int cmdIndex; /* cmdIndex is only given a value if -exec is given */
   int execArgc; 
   char** cmdArgs;
   char** execArgs;

   /* Parse command line arguments*/
   parseCommLine(argc, argv, &nameSwitch, &printSwitch, &execSwitch, &cmdIndex);

   /* There is 4 possibilities with the switch combinations. */
   /* 1. Only -print */
   /* 2. Only -exec  */
   /* 3. -name and -print */
   /* 4. -name and exec */

   /* 1. Command-line is: sfind filename -print */
   if(nameSwitch == FALSE && printSwitch == TRUE && execSwitch == FALSE)
   {
      if(isFile(argv[1]))
         printf("%s\n", argv[1]);
      else
      {
         /* Change directory to argument filename, argv[1] */
         checked_chDir(argv[1]);
         sfind_print(argv[1]);
      }
   }

   /* 2. Command-line is: fsfind filename -exec cmd ... \; */
   if(nameSwitch == FALSE && printSwitch == FALSE && execSwitch == TRUE)
   {
      cmdArgs = getCmdArgs(argc, argv, cmdIndex, &execArgc);

      /* If filename is just a file */
      if(isFile(argv[1]))
      {
         execArgs = argsToExecCmd(cmdArgs, argv[1], argv[cmdIndex], execArgc);
         execCmd(execArgs);
         free(execArgs);
      }
      else
      {
         checked_chDir(argv[1]);
         sfind_exec(argv[1], cmdArgs, argv[cmdIndex],  execArgc);
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

      if(isFile(argv[1]))
      {
         if(isSubStr(argv[1], argv[3]))
         {
            execArgs = argsToExecCmd(cmdArgs, argv[1], argv[cmdIndex],execArgc);
            execCmd(execArgs);
            free(execArgs);
         }
      }
      else
      {
         /* Change directory to argument filename, argv[1]*/
         checked_chDir(argv[1]);
         sfind_name_exec(argv[1], argv[3], cmdArgs, argv[cmdIndex], execArgc);
      }

      free(cmdArgs);
   }

   return 0;
}
