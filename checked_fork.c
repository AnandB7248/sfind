#include "checked_fork.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int checked_fork()
{
   pid_t tmp;

   if((tmp = fork()) < 0)
   {
      perror("Failed to fork: ");
      exit(-1);
   }

   return tmp;
}
