
#define BUFSZ 512
#define ERRBUFSZ 512

#define MYSH_PROMPT "mysh> "

#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include "mysh.h"
#ifndef SA_RESTART
#   define SA_RESTART 0x00000004
#endif


void alarm_handler(int sig) {

   printf("\n\nTimed Out 5 Seconds over...\n\n");
   alarm(0);  // alarm_time_remaining
   sigaction(SIGALRM, &oact, 0);  // reset handler
   exit(20);
}




int main(int argc, char **argv) {
	
	int i;
	int st;
	int linenum=0;
	char *buf=(char *)malloc(BUFSZ*sizeof(char)); 
	char *errbuf=(char *)malloc(ERRBUFSZ*sizeof(char)); 
	char *mysh = "";
	FILE *rfp=stdin;
	int fd[2];
        int rc,rcrd,rcwr,pid;
   	int c;

   // set new handler info in struct sigaction
   	act.sa_handler=alarm_handler;
   	sigemptyset(&act.sa_mask);
   	act.sa_flags=SA_RESTART;

   // notify kernel on handler for SIGALRM
   	sigaction(SIGALRM, &act, &oact);


	if (isatty(fileno(rfp))) {
	  mysh = MYSH_PROMPT;
	
		fprintf(stderr,"%s",mysh);
	}

	alarm(15);
	while (fgets(buf,BUFSZ,rfp)) 
	{
		alarm(15);
		linenum++;
		buf[strlen(buf)-1]=0;

		if ((rc=pipe(fd))>-1) {

                switch (pid=fork()) {
                        case -1:
                                fprintf(stderr,"Fork failed.\n");
                                return 0;
                                break;
                        case 0:
                                close(fd[1]);   // child closes write fd. child is listener.
                                rcrd=read(fd[0],buf,sizeof(buf));
                                if (rcrd>0) buf[rcrd]=0;
				if (*buf)
					{
					do_cmd(buf, BUFSZ, linenum,errbuf);
					}
				if(mysh)
				{
	        		fprintf(stderr,"%s",mysh);
				}
   				sigaction(SIGALRM, &oact, 0);  // reset handler
                                break;
                        default:
                                close(fd[0]);   // parent closes read fd. parent is talker.
                                rcwr=write(fd[1],buf,strlen(buf));
				wait(&st);
				exit(1);
                                break;
                    }
               }

        }
}

