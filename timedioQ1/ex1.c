// ch5_10.c

#define  _POSIX_SOURCE   1
#define  ALARMTMOUT      5
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#ifndef SA_RESTART
#   define SA_RESTART 0x00000004
#endif
struct sigaction oact, act;
int r;   // alarm_time_remaining

void alarm_handler(int sig) {

   printf("\n\nTimed Out 5 Seconds over...\n\n");
   alarm(r);  // alarm_time_remaining
   sigaction(SIGALRM, &oact, 0);  // reset handler
   exit(20);
}

int main() {
   char buf[250];
   int c;
  
   // set new handler info in struct sigaction
   act.sa_handler=alarm_handler;
   sigemptyset(&act.sa_mask);
   act.sa_flags=SA_RESTART;

   // notify kernel on handler for SIGALRM
   sigaction(SIGALRM, &act, &oact);
 
   r=alarm(ALARMTMOUT);
  
   printf("(5-sec)Enter>");

   fgets(buf,sizeof(buf),stdin);
   if(strlen(buf)>1)
   {
   printf("\nYou Entered %s\n", buf);
   }
  
   if(strlen(buf)<=1)
   {
   printf("\nYou Entered Nothing\n");
   }
  

   // Alarm time expired.   
   // Reset old alarm time expired.	
   alarm(r);  // alarm_time_remaining
   sigaction(SIGALRM, &oact, 0);  // reset handler

}
