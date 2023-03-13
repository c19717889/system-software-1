#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 8080

void *send_message(void *arg) {
    int sock = *(int*)arg;
    float celsius, fahrenheit;
    
    printf("Enter a temperature in Celsius: ");
    scanf("%f", &celsius);
    
    send(sock, &celsius, sizeof(celsius), 0);
    printf("Temperature sent to server.\n");
    
    read(sock, &fahrenheit, sizeof(fahrenheit));
    printf("Temperature in Fahrenheit: %f\n", fahrenheit);
    
    return NULL;
}

int main(int argc, char const *argv[]) {
    struct sockaddr_in address;
    int sock = 0;
    struct sockaddr_in serv_addr;
    pthread_t thread;
    
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }
    
    pthread_create(&thread, NULL, send_message, &sock);
    pthread_join(thread, NULL);

    return 0;
}