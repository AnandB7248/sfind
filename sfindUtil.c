#include <stdio.h>
#include <stdlib.h>
#include "sfindUtil.h"
#include "getPermission.h"
#include "charArrayList.h"
#include "checked_fork.h"
#include <dirent.h>
#include <sys/wait.h>
#define  TRUE 1
#define FALSE 0

void sfind_print(char* path)
{
   CharList *files; /* Files in the current directory, to be sorted in lexicographic order */
   int i; /* index for for-loop , see below */
   char* newPath; /* To be used when a directory is found, as then we need to recurse into it. */
   files = CharList_constructor();

   printf("%s\n", path);

   /* Retrieve all the contents of the directory, except for "." and ".."*/
   /* Sort them and save them into CharList files */
   sortFiles(&files);

   /* Now *files should have the contents of the current directory in lexicographic order */
   for(i = 0; i < files->numelements;i++)
   {
      if(isFile(files->arr[i]))
         printf("%s/%s\n", path, files->arr[i]); 

      else if(isDir(files->arr[i]))
      {
         /* Check to see if we can execute into directory */
         if(isExecSet(files->arr[i]))
         {
            checked_chDir(files->arr[i]);

            dynamicStrCat(&newPath, path, "/", files->arr[i]);
            /* Recurse */
            sfind_print(newPath);
            free(newPath);
          
            checked_chDir("..");
         }
         else
         {
            /* QUESTION: Print out the path to directory or just the directory name? */
            printf("Unable to enter into directory: %s\n", files->arr[i]);
         }
      }
   }

   files = delete(files);
}

void sfind_name_print(char* path, char* subStr)
{
   CharList *files;     /* Files in the current directory, to be sorted in lexicographic order */
   int i;               /* index for for-loop , see below */
   char* newPath;  /* To be used when a directory is found, as then we need to recurse into it. */
   files = CharList_constructor();

   /* Retrieve all the contents of the directory, except for "." and ".."*/
   /* Sort them and save them into CharList files */
   sortFiles(&files);
   /* Now *files should have the contents of the current directory in lexicographic order */
   for(i = 0; i < files->numelements;i++)
   {
      if(isSubStr(files->arr[i], subStr))
         printf("%s/%s\n", path, files->arr[i]);

      if(isDir(files->arr[i]))
      {
         if(isExecSet(files->arr[i]))
         {
            checked_chDir(files->arr[i]);

            dynamicStrCat(&newPath, path, "/", files->arr[i]);
            /* Recurse */
            sfind_name_print(newPath, subStr);
            free(newPath);
          
            checked_chDir("..");
         }
         else
         {
            /* QUESTION: Print out the path to directory or just the directory name? */
            printf("Unable to enter into directory: %s/%s\n",path, files->arr[i]);
         }
      }
   }

   files = delete(files);
}

void sfind_exec(char* path, char** cmdArgs, int execArgc, int origFD)
{
   CharList *files;
   char* newPath;
   char** execArgs;
   int i;

   files = CharList_constructor();
   sortFiles(&files);
   /* */
   if(fchdir(origFD) < 0)
   {
      perror("FCHDIR FAILED!\n");
      exit(-1);
   }
   /* */
   execArgs = argsToExecCmd(cmdArgs, path ,execArgc);
   execCmd(execArgs);
   free(execArgs);
   checked_chDir(path);

   for(i = 0; i < files->numelements; i++)
   {
      dynamicStrCat(&newPath, path, "/", files->arr[i]);

      if(isFile(files->arr[i]))
      {
         /* */
         if(fchdir(origFD) < 0)
         {
            perror("FCHDIR FAILED! INSIDE LOOP!\n");
            exit(-1);
         }
         /* */
         execArgs = argsToExecCmd(cmdArgs, newPath,execArgc);
         execCmd(execArgs);
         free(execArgs);
         checked_chDir(path);
      }
      else if(isDir(files->arr[i]))
      {
         if(isExecSet(files->arr[i]))
         {
            checked_chDir(files->arr[i]);
            sfind_exec(newPath, cmdArgs,execArgc, origFD);
            checked_chDir("..");
         }
         else
         {
            printf("Unable to enter into directory: %s\n", files->arr[i]);
         }
      }

      free(newPath);
   }

   files = delete(files);
}

void sfind_name_exec(char* path, char* subStr, char** cmdArgs, int execArgc, int origFD)
{
   CharList *files;
   int i;
   char* newPath;
   char** execArgs;

   files = CharList_constructor();
   sortFiles(&files);

   for(i = 0; i < files->numelements; i++)
   {
      dynamicStrCat(&newPath, path, "/", files->arr[i]);

      if(isSubStr(files->arr[i], subStr))
      {  /* */
         if(fchdir(origFD) < 0)
         {
            perror("fchdir failure!\n");
            exit(-1);
         }
         /* */
         execArgs = argsToExecCmd(cmdArgs, newPath, execArgc);
         execCmd(execArgs);
         free(execArgs);
         checked_chDir(path);
      }
      if(isDir(files->arr[i]))
      {
         if(isExecSet(files->arr[i]))
         {
            checked_chDir(files->arr[i]);

            /* Recurse */
            sfind_name_exec(newPath, subStr, cmdArgs,execArgc, origFD);
            checked_chDir("..");
         }
         else
         {
            printf("Unable to enter into directory: %s/%s\n", path, files->arr[i]);
         }
      }

      free(newPath);
   }
}

int isFile(char* filename)
{
   char* permBits;
   int boolean;
   getPermissionBits(filename, &permBits);
   if(permBits[0] == '-')
      boolean =  TRUE;
   else
      boolean =  FALSE;

   free(permBits);

   return boolean;
}

int isDir(char* filename)
{
   char* permBits;
   int boolean;

   getPermissionBits(filename, &permBits);

   if(permBits[0] == 'd')
      boolean =  TRUE;
   else
      boolean =  FALSE;

   free(permBits);

   return boolean;
}

int isExecSet(char* filename)
{
   char* permBits;
   int boolean;

   getPermissionBits(filename, &permBits);

   if(permBits[3] == 'x')
      boolean = TRUE;
   else
      boolean = FALSE;

   free(permBits);

   return boolean;
}

int isSubStr(const char* haystack, const char* needle)
{
   if(strstr(haystack, needle) != NULL)
      return TRUE;
   else
      return FALSE;
}

int bracesExist(int argc,char** argv, int cmdIndex)
{
   int counter = 0;
   int i;

   /* From argument after cmd to argument before \; */
   for(i = cmdIndex + 1; i < argc - 1; i++)
   {
      if(strcmp(argv[i], "{}") == 0)
         counter++;
   }

   return counter;
}

void sortFiles(CharList** sList)
{
   DIR *dir;
   struct dirent *dp;
   /* Change directory to path given by argument, directory */
   /*
   if(chdir(directory) < 0)
   {
      fprintf(stderr, "chdir: Unable to access: %s\n", directory);
      exit(-1);
   }
   */
   if((dir = opendir(".")) == NULL)
   {
      perror("Cannot open the current directory");
      exit(-1);
   }

   /* Place all the contents of the directory into the list */
   while((dp = readdir(dir)) != NULL)
   {
      add(*sList, dp->d_name);
   }

   /* Sort the contents of the list */
   sort(*sList);

   /* Close Directory */
   if((closedir(dir) < 0))
   {
      perror("Cannot close");
      exit(-1);
   }
}

void dynamicStrCat(char** combineNames, char* filename, const char* symbol, char* add)
{
   int length;
   int lengthF;
   int lengthS;
   int lengthA;

   if(combineNames == NULL || filename == NULL || symbol == NULL || add == NULL)
   {
      fprintf(stderr, "ERROR");
      exit(-1);
   }
   lengthF = strlen(filename);
   lengthS = strlen(symbol);
   lengthA = strlen(add);
   length = lengthF + lengthS + lengthA;

   *combineNames = (char*) malloc(length + 1);

   if(snprintf(*combineNames, length+1, "%s%s%s", filename, symbol, add) < 0)
   {
      perror("snprintf");
      exit(-1);
   }
}

void checked_chDir(char* filename)
{
   if(chdir(filename) < 0)
   {
      fprintf(stderr, "Failed to change into directory: %s\n", filename);
      exit(-1);
   }
}

char** argsToExecCmd(char** cmdArgs, char* filename, int execArgc)
{
   char** execArgs = (char**) malloc(sizeof(char**) * execArgc);
   int i;

   for(i = 0; i < (execArgc-1); i++)
   {
      if(strcmp(cmdArgs[i], "{}") ==  0)
         execArgs[i] = filename;
      else
         execArgs[i] = cmdArgs[i];
   }

   execArgs[i] = '\0';

   return execArgs;
}

char** getCmdArgs(int argc, char** argv, int cmdIndex, int* execArgc)
{
   int numArgs = argc - cmdIndex;
   char** cmdArgs = (char**)malloc(sizeof(char**) * numArgs);
   int indexCmdArgs, indexArgv;

   for(indexCmdArgs = 0, indexArgv = cmdIndex; indexCmdArgs < (numArgs - 1); indexCmdArgs++, indexArgv++)
   {
      cmdArgs[indexCmdArgs] = argv[indexArgv];
   }

   cmdArgs[indexCmdArgs] = '\0';
   *execArgc = numArgs;

   return cmdArgs;
}

void execCmd(char** argsToExec)
{
   /* Create another process and execute the specified command */
   pid_t pid;
   /*
   while(argsToExec[i] != '\0')
   {
      printf("Exec: %s\n", argsToExec[i++]);
   }
   */
   pid = checked_fork();

   if(pid == 0)
   {  /* Child */
      if(execvp(argsToExec[0], argsToExec) < 0)
      {
         fprintf(stderr, "Failed to exec: %s | [%s]\n", argsToExec[0], argsToExec[1]);
         exit(-1);
      }
   }
   else
   { /* Parent*/
      wait(NULL);
   }
}
