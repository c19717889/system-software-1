#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> /* for fork */
#include <sys/types.h> /* for pid_t */
#include <sys/wait.h> /* for wait */

int main() {
    pid_t pid=fork();
    int returnValue;
    returnValue = system("ls -la");
   /*Spawn a child to run the program.*/
    
    if (pid==0) { /* child process */
        char *argv[]={"echo","Echo is running now....",NULL};
	    sleep(15);
        execv("/bin/echo",argv);
        exit(127); /* only if execv fails */
    }
    else { /* pid!=0; parent process */
        printf("The parent keeps doing whats its doign!!");
        return returnValue;
	sleep(3);
    }
   
}