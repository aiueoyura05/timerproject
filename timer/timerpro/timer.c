#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>



void sig_handler(int signum) {
    if (signum == SIGUSR1) {
        pid_t pid = fork();
        if (pid == -1) {
            
            perror("fork");
            exit(1);
       
        } else if (pid == 0) {
            
            execl("/usr/bin/open", "open", "-a", "Terminal", "-n", "-e","/Users/yurainagaki/timer/timerpro/timer", NULL);
            exit(0);

        }
    }
}

int main(void){
   
    signal(SIGUSR1, sig_handler);
    
    
    printf("Send 'kill -s SIGUSR1 %d'to create new timer\n", getpid());

    while(1) {
        sleep(1);
    }

    return 0;
}
