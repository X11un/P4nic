#ifndef SYS_INFO_H
#define SYS_INFO_H

void getRamInfo(long *total, long *available);
void getCpuLoad(double *load1, double *load5, double *load15);
void getTopProcess(char *output, int max_length);

#endif