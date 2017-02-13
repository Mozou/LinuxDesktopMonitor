//
// Created by hu on 1/23/17.
//

#include "memory.h"
#include "cpu.h"
#include <string.h>
#include <stdlib.h>
#include <sys/statfs.h>
#include <time.h>

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

void log_hd_info(char *dir)
{
    MEMORY_INFO memory_info;
    int cpu_num = get_cpu_num();


    float cpu_usage[cpu_num + 1];
    get_cpus_usage(cpu_usage, cpu_num, 1);

    float mem_usage = get_physical_usage();
    float disk_usage = get_tf_usage("/");

    time_t t = time(NULL);
    struct tm *tp = localtime(&t);

    char nowtime[24];
    memset(nowtime, 0, sizeof(nowtime));
    strftime(nowtime, 24, "%Y-%m-%d %H:%M:%S", tp);

    FILE *log;
    log = fopen(dir, "a");
    if(log == NULL)
        perror("write log error");

    fprintf(log, "%s %f %f %f %f %f\n", nowtime, cpu_usage[0], cpu_usage[1], cpu_usage[2], mem_usage, disk_usage);

    fclose(log);

}