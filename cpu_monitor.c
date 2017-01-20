//
// Created by hu on 1/20/17.
//

#include "cpu_monitor.h"

int get_cpu_occupied(CPU_OCCUPY *cpu)
{
    FILE *file;
    char buff[256];

    file = fopen("/proc/stat", "r");
    if(file == NULL){
        fprintf(stderr, "open file error");
        return -1;
    }

    fgets(buff, sizeof(buff), file);

    sscanf(buff, "%s %u %u %u", cpu->name, &cpu->user, &cpu->nice, &cpu->system);

    fclose(file);
    return 0;
}