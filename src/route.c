#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "Route.h"
#include "SysInfo.h"


void handleRequest(int clientSocket, const char *request) {
    char response[2048];

    // Route 1 : RAM
    if (strncmp(request, "GET /ram", 8) == 0) {
        long totalRam, availableRam;
        getRamInfo(&totalRam, &availableRam);

        snprintf(response, sizeof(response),
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: application/json\r\n"
            "Access-Control-Allow-Origin: *\r\n\r\n"
            "{\n  \"totalRamKb\": %ld,\n  \"availableRamKb\": %ld\n}\n",
            totalRam, availableRam);
    } 
    // Route 2 : CPU
    else if (strncmp(request, "GET /cpu", 8) == 0) {
        double load1, load5, load15;
        getCpuLoad(&load1, &load5, &load15);

        snprintf(response, sizeof(response),
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: application/json\r\n"
            "Access-Control-Allow-Origin: *\r\n\r\n"
            "{\n  \"load1m\": %.2f,\n  \"load5m\": %.2f,\n  \"load15m\": %.2f\n}\n",
            load1, load5, load15);
    } 
    // Route 3 : Processus
    else if (strncmp(request, "GET /process", 12) == 0) {
        char procInfo[1024];
        getTopProcess(procInfo, sizeof(procInfo));

        snprintf(response, sizeof(response),
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/plain\r\n"
            "Access-Control-Allow-Origin: *\r\n\r\n"
            "%s", procInfo);
    } 
    // Erreur 404
    else {
        snprintf(response, sizeof(response),
            "HTTP/1.1 404 Not Found\r\n"
            "Content-Type: application/json\r\n"
            "Access-Control-Allow-Origin: *\r\n\r\n"
            "{\"erreur\": \"Route non trouvee.\"}\n");
    }

    // Envoie client
    write(clientSocket, response, strlen(response));
}