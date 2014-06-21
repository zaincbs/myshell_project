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
#include <dirent.h>

#define word_in_line 256
void word_count();
void do_cmd(char *buf, int len, int linenum, char *errbuf);
int parse_cmd(char *buf, char **vbuf, char *errbuf);
int builtin_cmd(char **argv, int linenum);
int process_cmd(char **argv, int linenum);
int printwaitstatus(FILE *wfp, int pid, int st);
struct sigaction oact, act;
int r;   // alarm_time_remaining
int mycounter = 0;
void char_count();
void line_count();
void mycat(char *xptr);
int mywc(char *cptr);
int numargs;
char buffer[500];

int myls() 
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
 }
 printf("\n");
 closedir(dir);
 return 0;
}





void mycat(char *xptr)
{
  int fd,error,ret;
  fd = open(xptr, O_RDONLY);
  if (fd<0)
    {
       error = errno;
       printf("Error Opening File:%d:::::\n%s", fd, strerror(error));
       return;
    }
  ret = read(fd, buffer,sizeof(buffer));

  if (ret == -1)
    {
       error = errno;
       perror("read");
       return;		
    }
  printf("\n%s\n", buffer);
  close(fd);
  memset(buffer,0,sizeof(buffer));

}




int printwaitstatus(FILE *wfp, int pid, int st) {

        fprintf(wfp,"\n");

        fprintf(wfp,"%6d=wait()",pid);

        if (WIFEXITED(st)) {
                fprintf(wfp,"exit: %3d\n", WEXITSTATUS(st));
        }
        else if (WIFSTOPPED(st)) {
                fprintf(wfp,"stop status: %3d\n", WSTOPSIG(st));
        }
        else if (WIFSIGNALED(st)) {
                fprintf(wfp,"termination signal: %3d\n", WTERMSIG(st));

                // fprintf(wfp,"\tcore dump: %s\n", WIFCORE(st) ? "yes" : "no");
        }

        return 0;
}


int builtin_cmd(char **argv, int linenum) {

        int st;

        if ((strcmp(*argv,"exit") == 0) ||
                  (strcmp(*argv,"ex") == 0) ||
                  (strcmp(*argv,"quit") == 0) ||
                  (strcmp(*argv,"q") == 0) ) {
		printf("I tried to exit");
                exit(1);
        }
        else if (strcmp(*argv,"cd") ==0) {
                if ((argv[1]) && (st=chdir(argv[1])) != 0) {
                        fprintf(stderr,"ERR: \"cd\" to '%s' failed! (Line=%d)\n",
                                argv[1],linenum);
                        return -1;
                }
                return 1;
        }
        else if (strcmp(*argv,"hello") ==0) {
                        fprintf(stderr,"\nHello! from process '%d'. (Line=%d)\n",getpid(),linenum);
                        return 1;
        }

        else if(strcmp(*argv,"mywc") == 0)
                {
			if(numargs<2)
			{
				printf("Warning *Atleast two Arguments*");
				return 1;
			}
			mywc(argv[1]);	
                        return 1;
                }


 	else if(strcmp(*argv,"mycat") == 0)
                {
			if(numargs<2)
			{
				printf("Warning *Atleast two Arguments*");
				return 1;
			}
			mycat(argv[1]);	
                        return 1;
                }

	else if(strcmp(*argv,"myls") == 0)
                {
                        myls();
			return 1;
                }

                

        return 0;
}




int process_cmd(char **argv, int linenum) {

        pid_t   cpid=fork();

        if (cpid<0) {
                fprintf(stderr,"ERR: \"fork\" error! (Line=%d)\n",
                        linenum);
                exit (-1);
        }
        else if (cpid==0) {
                // child executes in the foreground
                if (execvp(argv[0],argv) < 0) {
                        fprintf(stderr,"ERR: \"execv(%s)\" error! (Line=%d)\n",
                        argv[0], linenum);
                        _exit (errno);
                }
        }
        else {
                // parent .. waiting in the background.
                int st;

                cpid=wait(&st);
                // printwaitstatus(stdout,cpid,st);
        }
}

int parse_cmd(char *buf, char **vbuf, char *errbuf) {

        int i=0;

        char *delim=" ,\t\n";

        char *tok;

        tok=strtok(buf,delim);

        while (tok) {
                vbuf[i]=(char *)malloc(BUFSZ*sizeof(char));

                strcpy(vbuf[i],tok);

                tok=strtok(NULL,delim);
                i++;
        }

        vbuf[i]=0;

        return i;

}


void do_cmd(char *buf, int len, int linenum, char *errbuf) {

        int i=0;
        char *vbuf[128];

        int maxargs=sizeof(vbuf)/sizeof(char *);

        if ((numargs=parse_cmd(buf,vbuf,errbuf))==maxargs) {
                fprintf(stderr,"ERR: too many args (Line=%d)\n",linenum);
        }
        else {
                if (!builtin_cmd(vbuf,linenum) ) {
                        process_cmd(vbuf,linenum);
                }
        }

        for (i=0;i<numargs; i++) {
                free(vbuf[i]);
        }

        return;
}



int mywc(char *cptr)
{
	int spaces = 0; int crack = 0;
	char *buf = buffer;
	int lines = 0 ; int words = 0;
	int fd;
	int length = 500;
	int error;
	int mycounter = 0;
	ssize_t ret;
	int counter_index = 0;	
	///////////////////////////////////////////


		fd = open(cptr, O_RDONLY);

		if(fd<0)
		    {	
		       error = errno;
		       printf("Error Opening File:%d:::::\n%s", fd, strerror(error));
		       return 0;
		    }


	while(length != 0 && (ret = read(fd, buf, length))!= 0)
    	{	
     	error = errno;
      		if(ret == -1)
     		 {
         		if(error == EINTR)
		            continue;
		         perror("read");
			 return 0;
		         break;
		  }
	length = length - ret;
      	buf = buf + ret;
    	}
    
     buffer[strlen(buffer)-1] = 0;
     word_count();
     char_count();
     line_count(); 

  close(fd);
  return 0;

}



void word_count()
{
   int i;
   int words = 0;
   for(i=0;i<strlen(buffer);i++)
   {
    if(buffer[i] == '\n')
      {
       if(buffer[i+1] != ' ')
       {
            words++;
       }
      mycounter = 0;
       }
    if(buffer[i] != ' ' && buffer[i] != '\n')
    {
       if(buffer[i+1] == ' ')
       {
            words++;
       }
    }
  }

  printf("*%d*",words);
}



void char_count()
{
   int i;
   int crack=0;
   for(i=0;i<strlen(buffer);i++)
   {
    if(buffer[i] != ' ' && buffer[i]!= '\n' )
     {
       crack++;
     }
   }
   printf("*%zu*",strlen(buffer)+1);
}


void line_count()
{
   int i;
   int mycounter=0;
   int lines = 0;
   for(i=0;i<strlen(buffer);i++)
   {
    if(buffer[i] != '\n')
    {
       mycounter++;
       if(mycounter == word_in_line)
       {
           lines++;
       }
    }
    if(buffer[i] == '\n')
    {
      lines++;
      mycounter = 0;
    }
  }
  printf("*%d*", lines+1);
}

