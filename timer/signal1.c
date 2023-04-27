#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

void* timer2Function(void){
    int time_remaining; //*int型で時間の設定*//
    printf("Enter the time in seconds");
    scanf("%d", &time_remaining); 
    time_t start_time = time(NULL);//*time_t型の変数start_timeにおいてtime(NULL)は現在時刻の取得*//
    time_t elapsed_time = difftime(start_time, start_time); //*time_t型において0秒を表す＊//

    printf("Time remaining: %d seconds\n", time_remaining);//*0秒の時の表示*//
    
    while ((int)time_remaining > 0) {   
        time_t prev_elapsed_time = elapsed_time;/*残り時間は0秒である*/
        time_t current_time = time(NULL);/*現在時刻の取得*/
        elapsed_time = difftime(current_time, start_time);/*カウントダウン開始時刻と現在時刻の差から残り時間を出す*/
        if((int)prev_elapsed_time < (int)elapsed_time){/*整数型の宣言ではないため、(int)のキャスト演算子を用いて*/
            time_remaining = time_remaining - 1;/*残り時間が0以上の場合、180から1ずつ引いていく*/
            printf("Time remaining: %d seconds\n", time_remaining);
            
        } else {
            continue;
        }

}
    printf("Time's up!\n");


    return 0;
}

void sig_handler(int signum) {
    if (signum == SIGUSR1) {
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(1);
        } else if (pid == 0) {
            signal(SIGUSR1, SIG_DFL);
            execl("/usr/bin/open", "open", "-a", "Terminal", "-n", "-e", NULL);

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
