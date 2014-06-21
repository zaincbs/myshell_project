
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
   alarm(r);  // alarm_time_remaining
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

   	int c;

   // set new handler info in struct sigaction
   	act.sa_handler=alarm_handler;
   	sigemptyset(&act.sa_mask);
   	act.sa_flags=SA_RESTART;

   // notify kernel on handler for SIGALRM
   	sigaction(SIGALRM, &act, &oact);



 	alarm(15);




	if (isatty(fileno(rfp))) {
	  mysh = MYSH_PROMPT;
	
		fprintf(stderr,"%s",mysh);
	}

	while (fgets(buf,BUFSZ,rfp)) 
	{
		alarm(15);
		linenum++;

		buf[strlen(buf)-1]=0;

		if (*buf)
			do_cmd(buf, BUFSZ, linenum,errbuf);
	
		if (mysh) 
			fprintf(stderr,"%s",mysh);
	}
}

