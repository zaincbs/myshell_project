#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#define subject "PATH"
int main(int argc, char *argv[])
{
 
 printf("\nThe Environment Variable Path is: %s\n", getenv(subject));
 return 0;
}

