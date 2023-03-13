#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <syslog.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

void backup_dashboard(void) {
	pid_t  pid;

	pid = fork();
	if (pid == 0) // child
	{
		char *args[] = {
			"/bin/sh",
			"/workspaces/system-software-1/assigment1/src/scripts/backup_reports.sh",				   NULL
		};

		execvp(args[0], args);
		syslog(LOG_INFO, "AFTER EXEC");
	}

	else // parent
	{
		int status;
		
		if(wait(&status) == -1) { 
			syslog(LOG_ERR, "backup_dashboard.c: wait() failed");
		}


		if( (WIFEXITED(status)) ) {

			if( WEXITSTATUS(status) != 0 ) {
				syslog(LOG_ERR, "ERROR BACKING UP DASHNBOARD DIRECTORY; STATUS %d", WEXITSTATUS(status));	
			} else { 
				syslog(LOG_INFO, "Successfully backed up dashboard, STATUS %d", WEXITSTATUS(status));
			}	

		}
	}

	 
}

