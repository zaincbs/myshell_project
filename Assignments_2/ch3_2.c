#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
int main(int argc, char *argv[])
{
 
 char *newenv[20];
 char *newargv[20];

 printf("\nThe name of the program is %s\n", argv[0]);
 printf("\nThe PID of the program is %d\n",(int)getpid());

 if (argc > 1)
   {
    newargv[0] = argv[1];
    newargv[1] = argv[2];
    newargv[2] = 0;
   }

 else
   {
     newargv[0] = "ls";
     newargv[1] = "-l";
     newargv[2] = 0;
   }
     
 
  execvp(newargv[0], newargv);
 

 
  
 
 return 0;
}

