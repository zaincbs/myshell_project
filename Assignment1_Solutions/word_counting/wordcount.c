#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#define file "/home/myCode/1/mytestfile.txt"
#define word_in_line 256
#define BUFFER_SIZE 500

int spaces = 0; int crack = 0;
char buffer[BUFFER_SIZE];
char *buf = buffer;
int lines = 0 ; int words = 0;
int fd;
int length = 500;
int error;
int mycounter = 0;
ssize_t ret;
int counter_index = 0;
int main(int argc, char *argv[])
{
  errno = 0;
  //write and opening
  fd = open(argv[1], O_RDONLY);
  if(fd<0)
    {
       error = errno;
       printf("Error Opening File:%d:::::\n%s", fd, strerror(error));
       exit(1);
    }
  while(length != 0 && (ret = read(fd, buf, length))!= 0)
    {
     error = errno;
      if(ret == -1)
      {
         if(error == EINTR)
            continue;
         perror("read");
         break;
      }
      length = length - ret;
      buf = buf + ret;
    }
  length = strlen(buffer);

  while(counter_index < length)
  {
    // printf("%c", buffer[counter_index]);

    if(buffer[counter_index] == '\n')
    {
       lines++;
       if(buffer[counter_index+1] != ' ')
       {
            words++;
       }
      mycounter = 0;
    }

    if(buffer[counter_index] != ' ' && buffer[counter_index] != '\n')
    {
       if(buffer[counter_index+1] == ' ')
       {
            words++;
       }
    }

    if(buffer[counter_index] != '\n')
    {
       mycounter++;
       if(mycounter == word_in_line)
       {
           lines++;
       }
    }

    if(buffer[counter_index] == ' ')
     {
       spaces++;
     }

    if(buffer[counter_index] != ' ' && buffer[counter_index]!= '\n' )
     {
       crack++;
     }



    counter_index++;


  }



  printf("\n%d ",spaces);
  printf(" %d", crack);
  printf(" %d", lines);
  printf(" %d ", words);
  printf( "%s\n", argv[1]);
  // read only: this read and write implemented
  // doesnt care about the return values from the
  // read all it take cares of is -1.
  // But their are certain cases where the call
  // can be failled due to some blocking and synchronization issues.
  // In that case the read call can be reiussued.


   //Combination of ret and errno value can help in figuring out a problem.
  //ret returns the number of bytes read to the buffer in case of no error
  //Eg of combination: if ret == -1 and errno == EINTR than a signal was
  //received before any byte was read. And anothe tip is that if ret== -1
  //and errno != EINTR || errno != EAGAIN than their is a big problem
return 0;
}
