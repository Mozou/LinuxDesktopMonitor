//
// Created by hu on 2/13/17.
//

#include "system.h"
#include "cpu.h"
#include <sys/statfs.h>
#include <string.h>


void get_sys_info(SYSTEM_INFO *system_info)
{
    //init cpu info buffer
    int cnum = get_cpu_num();
    system_info->cpu_num = cnum;
    system_info->cpu_name = (char **)malloc(64 * cnum);
    for (int k = 0; k < cnum; ++k) {
        system_info->cpu_name[k] = (char *)malloc(64);
    }
    //get tf disk capacity
    struct statfs diskinfo;
    statfs("/", &diskinfo);
    unsigned long long total_disk = diskinfo.f_blocks * diskinfo.f_bsize;
    system_info->hd_cap = total_disk;

    //get memory capacity
    FILE *file;
    file = fopen("/proc/meminfo", "r");
    if(file == NULL)
        perror("open file error");

    char buff[64];
    char *p;
    fgets(buff, sizeof(buff), file);
    p = strtok(buff, ": ");
    p = strtok(NULL, " ");
    system_info->mem_cap = atoi(p);
    fclose(file);


    //get cpu model name
    memset(buff, 0, 64);
    FILE *cpufile;
    cpufile = fopen("/proc/cpuinfo", "r");
    for (int i = 0; i < cnum; ++i) {
        for (int j = 0; j < 5; ++j) {
            fgets(buff, 64, cpufile);
        }
        char *p;
        char str[64];
        p = strtok(buff, ": ");
        p = strtok(NULL, " ");
        p = strtok(NULL, "");
        strcpy(str, p);
        for (int k = 0; k < 64; ++k) {
            if(str[k] == '\n') str[k] = '\0';
        }
        strcpy(system_info->cpu_name[i], str);
//        strcpy(system_info->cpu_name[i], p);
        if(i == cnum - 1) break;
        while (fgets(buff, 64, cpufile))
        {
            char *p;
            p = strtok(buff, ": ");
            int flag;
            flag = strcmp("power", p);
            if(flag == 0) break;
        }
        fgets(buff, 64, cpufile);
    }

    fclose(cpufile);

//    strcpy(system_info->cpu_name[0], p);

}