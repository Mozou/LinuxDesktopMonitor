#include <stdio.h>
#include "cpu_monitor.h"
#include "memory_monitor.h"
#include <time.h>
#include <string.h>


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

int main() {

    log_hd_info("/home/hu/hd.log");
    return 0;
}