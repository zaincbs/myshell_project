#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>

struct stat buff;

void inode_info(char *file);

int main(int argc, char *argv[])
{
 DIR *dir;
 struct dirent *sd;
 dir = opendir(".");
 if (dir == NULL)
 {
   printf("Error at Opening Directory\n");
   exit(1);
 }

 while(  (sd = readdir(dir))  != NULL)
 {
     printf("%-4.20s  ", sd->d_name);
     /*if(!strcmp(argv[1], "-e"))
      {
        inode_info(sd->d_name); 
      }

      if(!strcmp(argv[2], sd->d_name))
      {
        printf("Found: %s\n", sd->d_name); 
      }*/

 }
 printf("\n");
 closedir(dir);
 return 0;
}

void inode_info(char *file)
{
    int exists;
    exists = lstat(file, &buff);
    if(exists < 0)
    {
      printf("File doesnt exists");
    }else
    {
        printf("%4ld %4ld %4d %4s\n",buff.st_ino, buff.st_size,buff.st_mode,ctime(&buff.st_ctime));
    }
}
