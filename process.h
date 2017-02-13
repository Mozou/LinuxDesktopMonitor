//
// Created by hu shaoyu on 17-2-5.
//

#ifndef PROCESS_H
#define PROCESS_H
typedef struct {
    int pid;
    char process_name[16];
    char state[4];
    char user[16];
    int cpu_usage;
    int mem_usage;
    char lauch_time[64];
    char running_time[64];
    int port;
}PROCESS_INFO;

int get_process_num();
void kill_process(int pid);
void log_procs_info(char *dir);
void get_proc_info();

#endif //PROCESS_PROCESS_H