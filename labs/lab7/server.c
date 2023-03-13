#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>

#define PORT 8080

void *connection_handler(void *);

int main(int argc, char const *argv[]) {
    int server_fd, new_socket, *new_sock;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    pthread_t thread_id;

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    while ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen))) {
        puts("Connection accepted");

        new_sock = malloc(sizeof(int));
        *new_sock = new_socket;

        if (pthread_create(&thread_id, NULL, connection_handler, (void *)new_sock) < 0) {
            perror("could not create thread");
            return 1;
        }

        puts("Handler assigned");
    }

    if (new_socket < 0) {
        perror("accept failed");
        return 1;
    }

    return 0;
}

void *connection_handler(void *socket_desc) {
    int sock = *(int *)socket_desc;
    int valread;
    float celsius, fahrenheit;

    valread = read(sock, &celsius, sizeof(celsius));
    printf("Temperature in Celsius: %f\n", celsius);

    fahrenheit = (celsius * 9 / 5) + 32;

    send(sock, &fahrenheit, sizeof(fahrenheit), 0);
    printf("Temperature in Fahrenheit: %f\n", fahrenheit);

    free(socket_desc);

    return NULL;
}