#include <stdio.h>
#include "SysInfo.h"


void getCpuLoad(double *load1, double *load5, double *load15) {

    FILE *file = fopen("/proc/loadavg", "r");

    fscanf(file, "%lf %lf %lf", load1, load5, load15);
    fclose(file);
}

