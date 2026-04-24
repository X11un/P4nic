#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SysInfo.h"


void getTopProcess(char *output, int maxLength) {
    // head -n 6 header + 5 premier process
    FILE *fp = popen("ps -eo pid,comm,%cpu,%mem --sort=-%cpu | grep -v 'ps' | head -n 6", "r");        // Trie decroisant +


    output[0] = '\0';
    char buffer[256];

    // Lecture ligne par ligne
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        if (strlen(output) + strlen(buffer) < (size_t)maxLength) {
            strcat(output, buffer);
        }
    }

    pclose(fp);
}