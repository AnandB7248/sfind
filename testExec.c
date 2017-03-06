#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
   if(execv(argv[1], (argv+1)) < 0)
   {
      printf("Failed to exec: [%s] \n", argv[1]);
      exit(-1);
   }

   return 0;
}
