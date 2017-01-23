//
// Created by hu on 1/20/17.
//

#include "cpu_monitor.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void get_cpu_occupy(CPU_OCCUPY *cpu_occupy)
{
    FILE *file;
    char buff[64];

    file = fopen("/proc/stat", "r");
    if(file == NULL)
        perror("open cpu occupy file error\n");

    fgets(buff, sizeof(buff), file);

    printf("%s", buff);

    char *p;

    p = strtok(buff, " ");
    printf("%s\n", p);
    p = strtok(NULL, " ");
    printf("%d\n", atoi(p));//user
    p = strtok(NULL, " ");
    printf("%d\n", atoi(p));//nice
    p = strtok(NULL, " ");
    printf("%d\n", atoi(p));//system
    p = strtok(NULL, " ");
    printf("%d\n", atoi(p));//idle
    p = strtok(NULL, " ");
    printf("%d\n", atoi(p));//iowait
    p = strtok(NULL, " ");
    printf("%d\n", atoi(p));//irq
    p = strtok(NULL, " ");
    printf("%d\n", atoi(p));//softirq
    p = strtok(NULL, " ");
    printf("%d\n", atoi(p));//stealstolen
    p = strtok(NULL, " ");
    printf("%d\n", atoi(p));//guest
//    cpu_occupy->user = atoi(p);
//    printf("%d\n", cpu_occupy->user);


    fclose(file);

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

//float get_cpu_usage()
//{
//    CPU_OCCUPY *cpu1;
//    CPU_OCCUPY *cpu2;
//
//    get_cpu_occupy(cpu1);
//    sleep(5);
//
//
//    int totalCpuTime1 = cpu1->user + cpu1->nice + cpu1->system + cpu1->idle +
//            cpu1->iowait + cpu1->irq + cpu1->softirq + cpu1->stealstolen + cpu1->guest;
//
//
//}