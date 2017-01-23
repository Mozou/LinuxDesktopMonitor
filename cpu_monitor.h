//
// Created by hu on 1/20/17.
//

#ifndef CPU_MONITOR_H
#define CPU_MONITOR_H

#include <stdio.h>
#include <stdlib.h>


typedef struct data{
    char name[6];

    int user;//    cpu_stat's user field
    int nice;//    cpu_stat's nice field
    int system;//  cpu_stat's sys field
    int idle;//    cpu_stat's idle field
    int iowait;
    int irq;//     cpu_stat's irq field
    int softirq;// cpu_stat's softirq field
    int stealstolen;
    int guest;
}CPU_OCCUPY;// CPU snapshot data

typedef struct{
    unsigned int processer_num;
    char name[64];
    float cpu_MHz;
}CPU_INFO;

void get_cpu_occupy(CPU_OCCUPY *cpu);

unsigned int get_cpu_num();

float get_cpu_usage();

#endif //CPU_MONITOR_H