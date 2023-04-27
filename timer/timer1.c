#include <stdio.h>
#include <time.h>

int main() {
    int time_remaining = 180;
    time_t start_time = time(NULL);

    while (time_remaining > 0) {
        int past_time = time(NULL);
        time_remaining = time_remaining - (int) difftime(past_time, start_time);
        printf("Time remaining: %d seconds\n", time_remaining);
       
    }

    printf("Time's up!\n");

    return 0;
}