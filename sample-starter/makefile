CC=gcc
objects = daemon.o backup_dashboard.o check_file_uploads.o collect_reports.o generate_reports.o lock_directories.o sig_handler.o unlock_directories.o update_timer.o 
headers = daemon_task.h 

assignment_daemon : $(objects)
	$(CC) -o assignment_daemon $(objects)

daemon.o : daemon.c $(headers)
	$(CC) -c daemon.c

backup_dashboard.o : backup_dashboard.c
	$(CC) -c backup_dashboard.c

check_file_uploads.o  :check_file_uploads.c
	$(CC) -c check_file_uploads.c

collect_reports.o : collect_reports.c
	$(CC) -c collect_reports.c

lock_directories.o : lock_directories.c
	$(CC) -c lock_directories.c

unlock_directories.o : unlock_directories.c
	$(CC) -c unlock_directories.c

sig_handler.o : sig_handler.c
	$(CC) -c sig_handler.c

clean:
	rm assignment_daemon $(objects)

