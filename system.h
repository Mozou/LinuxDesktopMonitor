//
// Created by hu on 2/13/17.
//

#ifndef PROJECT_SYSTEM_H
#define PROJECT_SYSTEM_H

#include <stdint.h>

typedef struct {
    char **cpu_name;
    int cpu_num;
    int mem_cap;
    long long hd_cap;
}SYSTEM_INFO;


void get_sys_info(SYSTEM_INFO *system_info);
#endif //PROJECT_SYSTEM_H
