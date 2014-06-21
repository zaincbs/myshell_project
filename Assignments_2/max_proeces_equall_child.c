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

 printf("\nMax Number of Processess for a Parent process is: %d\n", (int)sysconf(_SC_CHILD_MAX));

 return 0;
}

