#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

int main()
{
    FILE *rd;
    char buffer[50];
    sprintf(buffer,"ALanALanALan");
    rd=popen("wc -c","r"); // wc -c -> is the process which counts the number of characters passed. 2nd parameter is "w" which means pipe is opened in writing mode
    // fwrite(buffer,sizeof(char),strlen(buffer),rd); // to write the data into the pipe
    fread(buffer, 1, 40, rd); //will read only 50 characters
    printf("%s\n", buffer);
    pclose(rd);
}