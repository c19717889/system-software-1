#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> /* for fork */
#include <sys/types.h> /* for pid_t */
#include <sys/wait.h> /* for wait */


int main(void)
{
    pid_t pid=fork();
    char *name[50];
    FILE *fptr;
    fptr = fopen("log.txt","w");

    
   /*Spawn a child to run the program.*/
    
    if (pid=NULL) { /* child process */
        
        printf("Error, process not completed.....!\n");
    }
    else { 
        printf("Enter name: ");
        scanf("%s",&name);

        fprintf(fptr,"%s",name);
        fclose(fptr);
	    sleep(3);
    }

    
    
    return 0;
}
