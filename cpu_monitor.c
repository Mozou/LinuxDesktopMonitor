//
// Created by hu on 1/20/17.
//

#include "cpu_monitor.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void get_totalcpu_occupy(CPU_OCCUPY *cpu_occupy)
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
    strcpy(cpu_occupy->name, p);//name

    p = strtok(NULL, " ");
    cpu_occupy->user = atoi(p);//user

    p = strtok(NULL, " ");
    cpu_occupy->nice = atoi(p);//nice

    p = strtok(NULL, " ");
    cpu_occupy->system = atoi(p);//system

    p = strtok(NULL, " ");
    cpu_occupy->idle = atoi(p);//idle

    p = strtok(NULL, " ");
    cpu_occupy->iowait = atoi(p);//iowait

    p = strtok(NULL, " ");
    cpu_occupy->irq = atoi(p);//irq

    p = strtok(NULL, " ");
    cpu_occupy->softirq = atoi(p);//softirq

    p = strtok(NULL, " ");
    cpu_occupy->stealstolen = atoi(p);//stealstolen

    p = strtok(NULL, " ");
    cpu_occupy->guest = atoi(p);//guest
//    cpu_occupy->user = atoi(p);
//    printf("%d\n", cpu_occupy->user);


    fclose(file);

}

void get_cpus_occupy(CPU_OCCUPY *cpu_occupy, int cpu_nums)
{
    FILE *file;
    char buff[64];

    file = fopen("/proc/stat", "r");
    if(file == NULL)
        perror("open cpu occupy file error\n");

    int count = cpu_nums + 1;

    for (int i = 0; i < count; ++i) {
        fgets(buff, sizeof(buff), file);
        char *p;
        p = strtok(buff, " ");
        strcpy(cpu_occupy->name, p);//name
        p = strtok(NULL, " ");
        cpu_occupy->user = atoi(p);//user
        p = strtok(NULL, " ");
        cpu_occupy->nice = atoi(p);//nice
        p = strtok(NULL, " ");
        cpu_occupy->system = atoi(p);//system
        p = strtok(NULL, " ");
        cpu_occupy->idle = atoi(p);//idle
        p = strtok(NULL, " ");
        cpu_occupy->iowait = atoi(p);//iowait
        p = strtok(NULL, " ");
        cpu_occupy->irq = atoi(p);//irq
        p = strtok(NULL, " ");
        cpu_occupy->softirq = atoi(p);//softirq
        p = strtok(NULL, " ");
        cpu_occupy->stealstolen = atoi(p);//stealstolen
        p = strtok(NULL, " ");
        cpu_occupy->guest = atoi(p);//guest
        cpu_occupy++;
    }

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

float get_totalcpu_usage(int sec)
{
    CPU_OCCUPY cpu1;
    CPU_OCCUPY cpu2;

    get_totalcpu_occupy(&cpu1);
    sleep(sec);
    get_totalcpu_occupy(&cpu2);

    int totalCpuTime1 = cpu1.user + cpu1.nice + cpu1.system + cpu1.idle +
                        cpu1.iowait + cpu1.irq + cpu1.softirq + cpu1.stealstolen + cpu1.guest;

    int totalCpuTime2 = cpu2.user + cpu2.nice + cpu2.system + cpu2.idle +
                        cpu2.iowait + cpu2.irq + cpu2.softirq + cpu2.stealstolen + cpu1.guest;

    int total = totalCpuTime2 - totalCpuTime1;

    int idle = cpu2.idle - cpu1.idle;

    float usage = (float) (total - idle)  / total;

    return  usage;
}

float get_cpus_usage(float *cpu_usage, int cpu_nums ,int sec)
{

    CPU_OCCUPY cpu_occupy1[cpu_nums+1];
    CPU_OCCUPY cpu_occupy2[cpu_nums+1];

    get_cpus_occupy(cpu_occupy1, cpu_nums);
    sleep(1);
    get_cpus_occupy(cpu_occupy2, cpu_nums);

    int count = cpu_nums + 1;

    for (int i = 0; i <count ; ++i) {
        int totalTime1 = cpu_occupy1[i].user + cpu_occupy1[i].nice + cpu_occupy1[i].system + cpu_occupy1[i].idle +
                cpu_occupy1[i].iowait + cpu_occupy1[i].irq + cpu_occupy1[i].softirq + cpu_occupy1[i].stealstolen + cpu_occupy1[i].guest;
        int totalTime2 = cpu_occupy2[i].user + cpu_occupy2[i].nice + cpu_occupy2[i].system + cpu_occupy2[i].idle +
                         cpu_occupy2[i].iowait + cpu_occupy2[i].irq + cpu_occupy2[i].softirq + cpu_occupy2[i].stealstolen + cpu_occupy2[i].guest;
        int total = totalTime2 - totalTime1;
        int idle = cpu_occupy2[i].idle - cpu_occupy1[i].idle;
        cpu_usage[i] = (float) (total-idle) / total;
    }


    return  0;
}

