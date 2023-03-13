
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <syslog.h>

void unlock_directories() {
    printf("unlock directory functionality should go here. fork/chmod will be used here to change permissions");
     char* ps_list[] = {"chmod","777", NULL};
     pid_t  pid;
     
     // Your error checking for parameters  goes here!!!!
     if (argc == 1) { // only command no params
        pid = fork();
        if (pid == 0) // child
        {
           printf ("Executing command chmod...\n");
           execvp ("/bin/chmod", ps_list);
        }
        else // parent
        {
          int status=0;
          wait(&status);
          printf ("Child process is returned with: %d.\n",status);
        }
     } 
}
        