#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "SysInfo.h"

#define PORT 8080

int main() {
    int serverFd, newSocket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024];

    // Creation socket
    if ((serverFd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Erreur socket");
        exit(EXIT_FAILURE);
    }

    int opt = 1;
    setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // Config : reseau local + port 8080
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind
    if (bind(serverFd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Erreur bind");
        close(serverFd);
        exit(EXIT_FAILURE);
    }

    // Listen
    if (listen(serverFd, 5) < 0) {
        perror("Erreur listen");
        close(serverFd);
        exit(EXIT_FAILURE);
    }

    printf("API P4nic on ! Ecoute sur le port %d...\n", PORT);

    while (1) {
        newSocket = accept(serverFd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (newSocket < 0) {
            perror("Erreur accept");
            continue;
        }

        memset(buffer, 0, sizeof(buffer));
        read(newSocket, buffer, sizeof(buffer) - 1);

        char response[2048];

        if (strncmp(buffer, "GET /ram", 8) == 0) {
            long totalRam, availableRam;

            getRamInfo(&totalRam, &availableRam);

            snprintf(response, sizeof(response),
                "HTTP/1.1 200 OK\r\n"
                "Content-Type: application/json\r\n\r\n"
                "{\n  \"totalRamKb\": %ld,\n  \"availableRamKb\": %ld\n}\n",
                totalRam, availableRam);
        } else {
            snprintf(response, sizeof(response),
                "HTTP/1.1 404 Not Found\r\n"
                "Content-Type: application/json\r\n\r\n"
                "{\"erreur\": \"Route non trouvee. Essayez /ram\"}\n");
        }

        write(newSocket, response, strlen(response));
        close(newSocket);
    }

    close(serverFd);
    return 0;
}