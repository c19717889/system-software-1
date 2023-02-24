#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    int pipefd[2];
    int pipefd2[2];
    pid_t pid_ls, pid_awk, pid_sort;
    
    // Create the pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    
    // Fork the first child process to execute "ls -al"
    pid_ls = fork();
    if (pid_ls == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid_ls == 0) {
        // Child process: redirect stdout to the write end of the pipe
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        execlp("ls", "ls", "-al", NULL);
        perror("execlp ls");
        exit(EXIT_FAILURE);
    }
    
    // Fork the second child process to execute "awk '{ print $3 }'"
    pid_awk = fork();
    if (pid_awk == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid_awk == 0) {
        // Child process: redirect stdin to the read end of the pipe,
        // and stdout to a new pipe
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
        
        
        if (pipe(pipefd2) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
        dup2(pipefd2[1], STDOUT_FILENO);
        close(pipefd2[0]);
        close(pipefd2[1]);
        
        execlp("awk", "awk", "'{ print $3 }'", NULL);
        perror("execlp awk");
        exit(EXIT_FAILURE);
    }
    
    // Fork the third child process to execute "sort -u"
    pid_sort = fork();
    if (pid_sort == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid_sort == 0) {
        // Child process: redirect stdin to the read end of the second pipe
        close(pipefd[0]);
        close(pipefd[1]);
        close(STDIN_FILENO);
        dup2(pipefd2[0], STDIN_FILENO);
        close(pipefd2[0]);
        close(pipefd2[1]);
        
        execlp("sort", "sort", "-u", NULL);
        perror("execlp sort");
        exit(EXIT_FAILURE);
    }
    
    // Parent process: wait for all child processes to finish
    close(pipefd[0]);
    close(pipefd[1]);
    close(pipefd2[0]);
    close(pipefd2[1]);
    
    waitpid(pid_ls, NULL, 0);
    waitpid(pid_awk, NULL, 0);
    waitpid(pid_sort, NULL, 0);
    
    return 0;
}