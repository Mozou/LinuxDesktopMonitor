//
// Created by hu on 1/23/17.
//

#include "memory_monitor.h"
#include <string.h>
#include <stdlib.h>
#include <sys/statfs.h>

void get_memory_info(MEMORY_INFO *memory_info)
{
    FILE *file;
    file = fopen("/proc/meminfo", "r");

    if(file == NULL)
        perror("open file error");

    char buff[64];
    char *p;



    fgets(buff, sizeof(buff), file);
    p = strtok(buff, ": ");
    p = strtok(NULL, " ");
    memory_info->memTotal = atoi(p);

    fgets(buff, sizeof(buff), file);
    p = strtok(buff, ": ");
    p = strtok(NULL, " ");
    memory_info->memFree = atoi(p);

    fgets(buff, sizeof(buff), file);
    fgets(buff, sizeof(buff), file);
    p = strtok(buff, ": ");
    p = strtok(NULL, " ");
    memory_info->buffers = atoi(p);

    fgets(buff, sizeof(buff), file);
    p = strtok(buff, ": ");
    p = strtok(NULL, " ");
    memory_info->cached = atoi(p);

    fclose(file);
}

float get_physical_usage()
{
    MEMORY_INFO memory_info;
    get_memory_info(&memory_info);

    float used = memory_info.memTotal - memory_info.memFree - memory_info.buffers - memory_info.cached;

    float usage = (float)used / memory_info.memTotal;
}

float get_tf_usage(char *dir)
{
    struct statfs diskinfo;

    statfs(dir, &diskinfo);

    unsigned long long total_disk = diskinfo.f_blocks * diskinfo.f_bsize;
    unsigned long long free_disk = diskinfo.f_bfree * diskinfo.f_bsize;
    unsigned long long avail_disk = diskinfo.f_bavail * diskinfo.f_bsize;

    return (float) (total_disk - free_disk) / total_disk;

}