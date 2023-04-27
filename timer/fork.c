#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <util.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/ioctl.h>

int main(int argc, char **argv) {
    int master, slave;
    char buf[BUFSIZ];
    pid_t pid;

    if (openpty(&master, &slave, NULL, NULL, NULL) == -1) {
        perror("openpty");
        exit(EXIT_FAILURE);
    }

    pid = forkpty(&master, NULL, NULL, NULL);
    if (pid == -1) {
        perror("forkpty");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        /* Child process */
        execl("/bin/bash", "bash", (char *)NULL);
    }

    /* Parent process */
    while (1) {
        int n = read(master, buf, BUFSIZ);
        if (n <= 0) {
            break;
        }
        write(STDOUT_FILENO, buf, n);
    }

    close(master);
    close(slave);

    return 0;
}
