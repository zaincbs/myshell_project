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

 int newsize = (int)sysconf(_SC_OPEN_MAX);
 printf("\nThis Process can open %d Number of Files\n", newsize);

 return 0;
}

