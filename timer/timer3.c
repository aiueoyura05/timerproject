#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>
#include <curl/curl.h>
#include <pty.h>
#include <unistd.h>


void* timer1Function(void *arg) {
    int time_remaining= *(int*)arg; //*int型で時間の設定*//
    time_t start_time = time(NULL);//*time_t型の変数start_timeにおいてtime(NULL)は現在時刻の取得*//
    time_t elapsed_time = difftime(start_time, start_time); //*time_t型において0秒を表す＊//

    printf("Time remaining: %d seconds\n", time_remaining);//*0秒の時の表示*//
    
    while ((int)time_remaining > 0) {   
        time_t prev_elapsed_time = elapsed_time;/*残り時間は0秒である*/
        time_t current_time = time(NULL);/*現在時刻の取得*/
        elapsed_time = difftime(current_time, start_time);/*カウントダウン開始時刻と現在時刻の差から残り時間を出す*/
        if((int)prev_elapsed_time < (int)elapsed_time){/*整数型の宣言ではないため、(int)のキャスト演算子を用いて*/
            time_remaining = time_remaining - 1;/*残り時間が0以上の場合、180から1ずつ引いていく*/
            printf("Timer1 remaining: %d seconds\n", time_remaining);
        } else {
            continue;
        }

    }
    
    pthread_exit(NULL);
    
}
void* timer2Function(void *arg) {
    int time_remaining= *(int*)arg; //*int型で時間の設定*//
    time_t start_time = time(NULL);//*time_t型の変数start_timeにおいてtime(NULL)は現在時刻の取得*//
    time_t elapsed_time = difftime(start_time, start_time); //*time_t型において0秒を表す＊//

    printf("Time remaining: %d seconds\n", time_remaining);//*0秒の時の表示*//
    
    while ((int)time_remaining > 0) {   
        time_t prev_elapsed_time = elapsed_time;/*残り時間は0秒である*/
        time_t current_time = time(NULL);/*現在時刻の取得*/
        elapsed_time = difftime(current_time, start_time);/*カウントダウン開始時刻と現在時刻の差から残り時間を出す*/
        if((int)prev_elapsed_time < (int)elapsed_time){/*整数型の宣言ではないため、(int)のキャスト演算子を用いて*/
            time_remaining = time_remaining - 1;/*残り時間が0以上の場合、180から1ずつ引いていく*/
            printf("Timer2 remaining: %d seconds\n", time_remaining);
        } else {
            continue;
        }

    }
    
    pthread_exit(NULL);
    return NULL;/*なんでこれがいるのかいまいちわかっていない*/
}

int main(){
    pthread_t thread1,thread2;
    int time1,time2;

    printf("Enter the time for timer 1 in seconds");
    scanf("%d",&time1);
    printf("Enter the time for timer 2 in seconds");/*2つのスレッドでの並列処理*/
    scanf("%d",&time2);

    pthread_create(&thread1,NULL,&timer1Function, (void*)&time1);/**/
    pthread_create(&thread2,NULL,&timer2Function, (void*)&time2);

    pthread_join(thread1,NULL);/**/
    printf("timer1 times up!\n");
    pthread_join(thread2,NULL); /*スレッドの終了待ち*/
    printf("timer2 times up!\n");
    return 0;

}
   

    

   