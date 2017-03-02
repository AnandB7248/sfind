#include <stdio.h>
#include "parseCommLine.h"

#define  TRUE 1
#define FALSE 0

int main(int argc, char* argv[])
{
   int nameSwitch  = FALSE;
   int printSwitch = FALSE;
   int execSwitch  = FALSE;
   int cmdIndex;

   /* Parse command line arguments*/
   parseCommLine(argc, argv, &nameSwitch, &printSwitch, &execSwitch, &cmdIndex);

   printf("name: %d\n", nameSwitch);
   printf("print: %d\n", printSwitch);
   printf("exec: %d\n", execSwitch);
   if(execSwitch == TRUE)
      printf("cmdIndex: %d\n\ncmd: %s\n", cmdIndex, argv[cmdIndex]);
   return 0;

