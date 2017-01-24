#include <stdio.h>
#include "cpu_monitor.h"
#include "memory_monitor.h"
#include <time.h>
#include <string.h>


void log_hd_info(char *dir)
{
    MEMORY_INFO memory_info;
    float cpu_usage = get_cpu_usage(1);
    float mem_usage = get_physical_usage();
    float disk_usage = get_tf_usage("/");

    time_t t = time(NULL);
    struct tm *tp = localtime(&t);

    char nowtime[24];
    memset(nowtime, 0, sizeof(nowtime));
    strftime(nowtime, 24, "%Y-%m-%d %H:%M:%S", tp);

    printf("%d/%d/%d\n", tp->tm_mon+1, tp->tm_mday, tp->tm_year + 1900);
    printf("%d:%d:%d\n", tp->tm_hour, tp->tm_min, tp->tm_sec);

    FILE *log;
    log = fopen(dir, "a");
    if(log == NULL)
        perror("write log error");

    fprintf(log, "%s %f %f %f", nowtime, cpu_usage, mem_usage, disk_usage);

    fclose(log);

}

int main() {

    log_hd_info("/home/hu/hd.log");
    return 0;
}