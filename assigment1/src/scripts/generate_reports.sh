#!/bin/bash

audit_file="audit-report-$(date +'%d-%m-%Y').txt"
syslog_report="syslog-report-$(date +'%d-%m-%Y').txt"

date=$(date +'%b  %-d')

#generate audit log 
sudo ausearch  -ts today -k xml_upload_watch | sudo aureport -f -i  > /workspaces/system-software-1/assigment1/manufacturing_company_reports/$audit_file

sudo cat /var/log/daemon.log |  grep -a "$date.*MAN-DAEMON-LOGGER" >  /workspaces/system-software-1/assigment1/manufacturing_company_reports/$syslog_report

