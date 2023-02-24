/*
The tricky part is making certain to create the pipe (or pipes) BEFORE creating the child process. 
That way the parent and the child will share the same set of file descriptors for the pipe(s).

Here’s a pretty simple demo program that sends 0 through 9 from the parent process to the child process,
each time waiting for a message from the child. So the parent sends ‘0’ (through a pipe), 
the child reads the ‘0’ from the same pipe, then sends that ‘0’ back to the parent through a different 
pipe, and the parent reads that ‘0’ from that pipe. There are lots of texts displayed to show the 
activity. The program assumes that each of the system calls works. You really should check for 
system call failure in robust code.
*/


#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
 
int main(void) 
{ 
    int par_to_child[2];           /* pipe from parent to child */ 
    int child_to_par[2];           /* pipe from child to parent */ 
    int child;                     /* child's PID */ 
    char parsend[100]; 
    char parrecv[100]; 
    char childsend[100]; 
    char childrecv[100]; 
 
    /* Setup info texts */ 
    strcpy(parsend,"Parent sent X\n"); 
    strcpy(childsend,"Child sent X\n"); 
    strcpy(parrecv,"Parent received X\n"); 
    strcpy(childrecv,"Child received X\n"); 
 
    /* Create the pipes. */ 
    pipe(par_to_child); 
    pipe(child_to_par); 
 
    /* Create the child process */ 
    child = fork(); 
 
    /* Run the parent's code */ 
    if (child != 0) { 
        /* parent */ 
        int i; 
        char msg, msgin; 
        for(i=0;i<5;i++) { 
            msg = '0' + i; 
            parsend[strlen(parsend)-2] = msg; 
            write(1,parsend,strlen(parsend)); 
            write(par_to_child[1],&msg,1); 
 
            read(child_to_par[0],&msgin,1); 
            parrecv[strlen(parrecv)-2] = msgin; 
            write(1,parrecv,strlen(parrecv)); 
        } 
        exit(0); 
    } else 
 
    /* Run the child's code */ 
    { 
        /* child */ 
        int i; 
        char msgin; 
        for(i=0;i<5;i++) { 
            read(par_to_child[0],&msgin,1); 
            childrecv[strlen(childrecv)-2] = msgin; 
            write(1,childrecv,strlen(childrecv)); 
 
            childsend[strlen(childsend)-2] = msgin; 
            write(1,childsend,strlen(childsend)); 
            write(child_to_par[1],&msgin,1); 
        } 
        exit(0); 
    } 
} 