#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "Route.h"

#define PORT 8080

int main() {
    int serverFd, newSocket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024];

    // Creation socket et configuration
    if ((serverFd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Erreur socket");
        exit(EXIT_FAILURE);
    }

    int opt = 1;
    setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(serverFd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Erreur bind");
        close(serverFd);
        exit(EXIT_FAILURE);
    }

    if (listen(serverFd, 5) < 0) {
        perror("Erreur listen");
        close(serverFd);
        exit(EXIT_FAILURE);
    }

    printf("API P4nic on ! Ecoute sur le port %d...\n", PORT);

    // Boucle du serveur
    while (1) {
        newSocket = accept(serverFd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (newSocket < 0) {
            continue;
        }

        memset(buffer, 0, sizeof(buffer));
        read(newSocket, buffer, sizeof(buffer) - 1);

        handleRequest(newSocket, buffer);

        close(newSocket);
    }

    close(serverFd);
    return 0;
}