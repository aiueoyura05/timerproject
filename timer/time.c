#include <stdio.h>
#include <time.h>

int main() {
    int time_remaining = 180;
    time_t start_time = time(NULL);

    while (time_remaining > 0) {         
        time_t current_time = time(NULL);
        time_t elapsed_time = difftime(current_time, start_time);
        time_remaining = time_remaining - (int) elapsed_time;
        printf("Time remaining: %d seconds\n", time_remaining);
    }

    printf("Time's up!\n");

    return 0;
}




