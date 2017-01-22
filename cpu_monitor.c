//
// Created by hu on 1/20/17.
//

#include "cpu_monitor.h"
#include <stdio.h>

void get_cpu_occupied(CPU_OCCUPY *cpu)
{
    FILE *file;
    char buff[128];

    file = fopen("/proc/stat", "r");
    if(file == NULL)
        perror("open cpu occupy file error\n");

    int cpu_num = -1;
    while (fgets(buff, sizeof(buff), file) != NULL)
    {
        if(buff[0] == 'c') {
            cpu_num++;
            printf("%s", buff);
        } else break;
    }
    printf("cpu nums:%d", cpu_num);

    return 0;
}

unsigned int get_cpu_num()
{
    FILE *file;
    char buff[128];

    file = fopen("/proc/stat", "r");
    if(file == NULL)
        perror("open cpu occupy file error\n");

    int cpu_num = -1;
    while (fgets(buff, sizeof(buff), file) != NULL)
    {
        if(buff[0] == 'c') {
            cpu_num++;
        } else break;
    }

    return cpu_num;
}