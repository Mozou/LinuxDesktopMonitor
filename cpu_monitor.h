//
// Created by hu on 1/20/17.
//

#ifndef CPU_MONITOR_H
#define CPU_MONITOR_H

#include <stdio.h>
#include <stdlib.h>


typedef struct data{
    char name[10];
    unsigned int user;//    cpu_stat's user field
    unsigned int nice;//    cpu_stat's nice field
    unsigned int system;//  cpu_stat's sys field
    unsigned int idle;//    cpu_stat's idle field
    unsigned int irq;//     cpu_stat's irq field
    unsigned int softirq;//  cpu_stat's softirq field
}CPU_OCCUPY;

typedef struct{
    unsigned int processer_num;
    char name[64];
    float cpu_MHz;
}CPU_INFO;

void get_cpu_occupied(CPU_OCCUPY *cpu);

unsigned int get_cpu_num();

#endif //CPU_MONITOR_H