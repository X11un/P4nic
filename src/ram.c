#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SysInfo.h"


void GetRamInfo(long *total, long *available) {

    FILE *file = fopen("/proc/meminfo", "r");

    char line[256];
    // Lecture ligne par ligne 
    while (fgets(line, sizeof(line), file)) {
        // Recherche MemTotal
        if (strncmp(line, "MemTotal:", 9) == 0) {
            sscanf(line, "MemTotal: %ld kB", total);
        }
        // Recherche MemAvailable
        else if (strncmp(line, "MemAvailable:", 13) == 0) {
            sscanf(line, "MemAvailable: %ld kB", available);
        }
    }
    fclose(file);
}