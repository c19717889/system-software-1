date=$(date +'%d-%m-%Y')


tar -czf /workspaces/system-software-1/assigment1/backups/dashboard-backup-${date}.tar.gz -C /workspaces/system-software-1/assigment1/dashboard_system --transform "s|dashboard_system|dashboard-system-backup-${date}|"  
