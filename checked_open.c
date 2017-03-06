#include "checked_open.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int checked_open(char* path, int oflags)
{
   int fd;

   if((fd = open(path, oflags)) < 0)
   {
      perror("Open failed!");
      exit(-1);
   }

   return fd;
}
