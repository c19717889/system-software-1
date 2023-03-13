#include <unistd.h>
#include <syslog.h>

void check_file_uploads(void) {
        char *manufacturing_xml = "/workspaces/system-software-1/assigment1/managers_xml_upload/manufacturing_report.xml"; 

        char *warehouse_xml = "/workspaces/system-software-1/assigment1/managers_xml_upload/warehouse_report.xml"    ;

        char *sales_xml = "/workspaces/system-software-1/assigment1/managers_xml_upload/sales_report.xml";

         char *distribution_xml = "/workspaces/system-software-1/assigment1/managers_xml_upload/distribution_report.xml";


        char *files[] = {manufacturing_xml ,  warehouse_xml, sales_xml, distribution_xml};
	
	syslog(LOG_INFO, "CHECKING FOR UPLOADED XML REPORTS");

        for(int i = 0; i < 4; ++i) {

                if( access(files[i], F_OK) == -1) {
                        syslog(LOG_INFO,"File %s hasn't been uploaded by the manager", files[i]);
                } 

        }

}

      
