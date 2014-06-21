#include <sys/types.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
//////////////////////
int fd;
int fd2;
int ret;
char buffer[4096], mychar;
ssize_t bytes_read;
int indexer = 0;
int counter_line = 0;
//////////////////////

int main(int argc, char *argv[])
{

 fd = open("myfile.txt", O_CREAT | O_APPEND | O_RDONLY , 777);
 if (fd<0)
 {
   printf("\n%s\n", strerror(errno));
   exit(1);
 }
// int dup2(int oldfd, int newfd);
//dup2() makes newfd be the copy of oldfd, closing newfd first if  necessary,
// but note the following:

//       *  If  oldfd  is  not a valid file descriptor, then the call fails, and
//        newfd is not closed.
//       *  If oldfd is a valid file descriptor, and newfd has the same value as
//        oldfd, then dup2() does nothing, and returns newfd.


 ret = dup2(fd,0);
 printf("Zain is: %d", ret);
 if (ret<0)
 {
   printf("\n%s\n", strerror(errno));
   exit(1);
 }
 
  bytes_read = read(fd, buffer, sizeof(buffer));
  if(bytes_read == -1)
  {
  perror("Error Reading");
  }

  fd2 = open("myoutput.txt", O_CREAT | O_WRONLY, 777);

  if (fd2<0)
  {
   perror("Error in fd2");
   exit(1);
  }

  ret = dup2(fd2,1);
  printf("%s" , buffer);
  while(indexer <= strlen(buffer))
  {
      if(buffer[indexer] == '\n')
      {
        counter_line++;
      }
     indexer++;
  }
  fprintf(stderr, "\nPrinting to stderror line:%d\n", counter_line);

  close(fd);
  close(fd2);

 return 0;
}
