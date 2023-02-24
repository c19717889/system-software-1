#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *fp;
    char buffer[100];
    char message[] = "Hello, child process!";

    fp = popen("cat", "w");
    if (fp == NULL) {
        fprintf(stderr, "Popen failed");
        return 1;
    }

    fwrite(message, strlen(message) + 1, 1, fp);
    pclose(fp);

    return 0;
}