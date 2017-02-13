//
// Created by hu on 1/23/17.
//

#ifndef MEMORY_MONITOR_H
#define MEMORY_MONITOR_H

#include <stdio.h>

typedef struct{
    int memTotal;
    int memFree;
    int buffers;
    int cached;
}MEMORY_INFO;

void get_memory_info(MEMORY_INFO *memory_info);

float get_sys_usage();

float get_physical_usage();

float get_tf_usage(char *dir);  //get designated directory capacity

void log_hd_info(char *dir);

#endif //MEMORY_MONITOR_H