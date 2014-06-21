#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>

struct str{
     char va[20];
     char vb[20];
     char tname[20];
     char tname1[20];
};

typedef struct str node;

void *print(node *fptr);

pthread_t t1,t2;
int main(int argc, char *argv[])
{
 node *ptr;
 ptr = (node *)malloc(sizeof(node));
 strcpy(ptr->va,"Hello");
 strcpy(ptr->vb,"World");
 strcpy(ptr->tname,"Thread1");
 strcpy(ptr->tname1,"Thread2");
 void *status1;
 void *status2;  

 pthread_create(&t1, NULL,(void*)print,ptr);

 pthread_create(&t2, NULL,(void*)print,ptr);

 pthread_join(t1, &status1);
 pthread_join(t2, &status2);

 free(ptr);
 

 

 return 0;
}



void *print(node *fptr)
{
   int i;

   char tid2[20];
   for(i=0;i<5;i++)
   {
   pthread_t tid=pthread_self();
   if(pthread_equal(tid,t1))
   {  
     strcpy(tid2,"Thread1");
   }
   else
   { 
      strcpy(tid2,"Thread2");
   }

   printf("%s:%s %s\n",tid2,fptr->va,fptr->vb);
   sleep(1);
   }

   return 0;
}

