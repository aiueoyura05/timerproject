#include <stdio.h>
#include <unistd.h>

int main() {
    int seconds = 180;  

    while (seconds > 0) {
        printf("残り時間: %d秒\n", seconds);
        sleep(1);  
        seconds--;  
    }

    printf("タイムアップ！\n");

    return 0;
}
