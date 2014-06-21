#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#define file "/home/myCode/1/mytestfile.txt"

char buffer[800];
int fd;
int error;
ssize_t ret;
int indexer = 1;


int main(int argc, char *argv[])
{
if (argc<2)
{
  printf("\nvery few arguments\n");
  exit(1);
}

while(indexer<argc)
{
  fd = open(argv[indexer], O_RDONLY);
  if (fd<0)
    {
       error = errno;
       printf("Error Opening File:%d:::::\n%s", fd, strerror(error));
       exit(1);
    }

  ret = read(fd, buffer,sizeof(buffer));

  if (ret == -1)
    {
       error = errno;
       perror("read");
    }
  printf("\n%s\n", buffer);
  close(fd);
  memset(buffer,0,sizeof(buffer));
  indexer++;
}

  return 0;
}
