#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

volatile sig_atomic_t g_flag = 0;

void handle_signal(int sig) {
    g_flag = 1;
}

int main(void) {
    int time_remaining = 180; // タイマー時間を180秒に設定
    struct timespec t = {0, 100000000}; // 100ms
    time_t start_time, elapsed_time, prev_elapsed_time;

    signal(SIGUSR1, handle_signal);

    while (1) {
        if (g_flag) {
            // シグナルが発生したらタイマーを開始する
            printf("Timer started!\n");
            start_time = time(NULL);
            elapsed_time = difftime(start_time, start_time);
            printf("Time remaining: %d seconds\n", time_remaining);
            g_flag = 0;
        }

        // タイマーが動作中の場合、残り時間をカウントダウンする
        if ((int)time_remaining > 0) {
            prev_elapsed_time = elapsed_time;
            elapsed_time = difftime(time(NULL), start_time);
            if ((int)prev_elapsed_time < (int)elapsed_time) {
                time_remaining = time_remaining - 1;
                printf("Time remaining: %d seconds\n", time_remaining);
            }
        }

        // タイマーが終了した場合、ループを抜ける
        if ((int)time_remaining == 0) {
            printf("Timer finished!\n");
            break;
        }

        nanosleep(&t, NULL);
    }

    return 0;
}
