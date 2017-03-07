# sfind
Program: sfind

Description: sfind, simplified find.
             Program that acts like the UNIX find utility.


To use the program, simply call make.
From then the proper usage of the program is:

      ./sfind filename [-name str] -print | -exec cmd ... ;

      filename - Starting place of sfind.
                  If filename represents a regular file, only that file will be process.
                  If filename represents a directory, then sfind recursively traverses the hierarchy.

      Switches:
         -name  - OPTIONAL: To be used if looking for specific file that contains substring as indicaed by str that follows -name.
         -print - Simply prints the hierarchy traversal of sfind starting from filename.
         -exec  - Executes the cmd for every traversal of sfind starting from the filename.
                  Contents that follow cmd to ; are command-line arguments to cmd.
                  If {} is present between cmd and ;, then the path traversal is given as command-line argument to cmd.

      NOTE: Must have either -print OR -exec. 
      NOTE: May need to use "\;", instead of ";",  as most shells process this as a delimiting a sequence of commands to execute.
