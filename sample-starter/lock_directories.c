
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdio.h>
#include <syslog.h>

//would be better off to write to a file, rather than printf to screen

//all files will repeat a similar structure to this file

//locks directories - chmod to block read and writes when creating back-up

void lock_directories(int argc,char *argv[]) {
    //posibly change from 444.
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