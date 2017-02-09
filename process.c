//
// Created by hu on 17-2-9.
//

#include <stdio.h>
#include "process.h"
#include <string.h>
#include <sys/types.h>
#include <sys/signal.h>
#include <stdlib.h>
#include <time.h>

int get_process_num()
{
    FILE *file =popen("ps -A opid", "r");
    char buff[8];
    fgets(buff, 8, file);
    int count = 0;
    while (fgets(buff, 8, file) != NULL)
    {
        count++;
    }
    pclose(file);
    return count;
}

void kill_process(int pid)
{
    kill(pid, SIGTERM);
}

//void log_procs_info()
//{
//    FILE *file = popen("ps -A opid", "r");
//    char buff[8];
//    fgets(buff, 8, file);
//    char *p;
//    int pid;
//    FILE *proc_file;
//    char proc_name[64] = {0};
//    while(fgets(buff, 8, file) != NULL)
//    {
//        p = &buff;
//        pid = atoi(p);
//        sprintf(proc_name, "/proc/%d/stat", pid);
//        proc_file = popen(proc_name, "r");
//
//    }
//}

void get_proc_info()
{
    int num = get_process_num();
    PROCESS_INFO procs[num];
    FILE *file = popen("ps -A c opid", "r");
    char buff[8];
    int pid = 0;
    fgets(buff, 8, file);
    int i = 0;
    while (fgets(buff, 8, file) != NULL) {
//        pid =atoi(buff);
//        procs[i].pid = pid;
//        i++;
        char *p;
        p = strtok(buff, " ");
        pid = atoi(p);
        procs[i].pid = pid;

    }


}

void log_procs_info(char *dir)
{
    FILE *file = popen("ps -A c opid,stat,user,stime,etime,args", "r");
    char buff[64];

    time_t t = time(NULL);
    struct tm *tp = localtime(&t);

    char nowtime[24];
    memset(nowtime, 0, sizeof(nowtime));
    strftime(nowtime, 24, "%Y-%m-%d", tp);

    FILE *log = fopen(dir, "w");
    fgets(buff, 64, file);
    fprintf(log, "date %s", buff);
    while (fgets(buff, 64, file) != NULL)
    {
        fprintf(log, "%s %s", nowtime, buff);

    }
}