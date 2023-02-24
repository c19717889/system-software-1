#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd[2];
    pid_t pid;
    char message[] = "Hello, child process!";

    // Create a pipe
    if (pipe(fd) == -1) {
        fprintf(stderr, "Pipe failed");
        return 1;
    }

    // Fork a child process
    pid = fork();
    if (pid < 0) {
        fprintf(stderr, "Fork failed");
        return 1;
    }

    if (pid == 0) {  // Child process
        char buffer[100];

        close(fd[1]);  // Close the write end of the pipe
        read(fd[0], buffer, sizeof(buffer));
        printf("Child received message: %s\n", buffer);

        close(fd[0]);  // Close the read end of the pipe
    } else {  // Parent process
        close(fd[0]);  // Close the read end of the pipe
        write(fd[1], message, strlen(message) + 1);
        printf("Parent sent message: %s\n", message);

        close(fd[1]);  // Close the write end of the pipe
    }

    return 0;
}