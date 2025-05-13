#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define URL "https://example.com"
#define INITIAL_DELAY_SECONDS (20 * 60) // 20 minutes
#define REPEAT_INTERVAL_SECONDS (5 * 60) // 5 minutes

void daemonize() {
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }
    if (pid > 0) {
        // Parent process exits
        exit(EXIT_SUCCESS);
    }

    // Child process continues
    if (setsid() < 0) {
        perror("setsid failed");
        exit(EXIT_FAILURE);
    }

    // Close standard file descriptors
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    // Redirect them to /dev/null
    open("/dev/null", O_RDWR);
    dup(0);
    dup(0);
}

int main() {
    // Daemonize the process
    daemonize();

    // Wait for 20 minutes initially
    sleep(INITIAL_DELAY_SECONDS);

    // Infinite loop to open URL repeatedly
    while (1) {
        // Open the URL in the default browser
        char command[256];
        snprintf(command, sizeof(command), "xdg-open %s", URL);
        system(command);

        // Wait for the repeat interval
        sleep(REPEAT_INTERVAL_SECONDS);
    }

    return 0;
}