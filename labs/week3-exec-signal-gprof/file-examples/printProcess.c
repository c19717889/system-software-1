#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
//    int returnValue;
//    returnValue = system("ps aux");
//    int searchProcess = system("ps aux | grep -i '337'");
    int killProcess = system("ps aux | kill -9 337'");
   return killProcess;
//    return returnValue;

// printf("All Processes: %d", returnValue);
// printf("Single Processes: %d", searchProcess);
   
// return 0;
   
}
