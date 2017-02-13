#include <stdio.h>
#include <memory.h>
#include "cpu.h"
#include "system.h"

int main() {

    SYSTEM_INFO systemInfo;
    get_sys_info(&systemInfo);
    printf("printing systeminfo struct in the main\n");
    printf("%s\n", systemInfo.cpu_name[0]);
    printf("%s\n", systemInfo.cpu_name[1]);
    printf("%d\n", systemInfo.hd_cap >> 20);
    printf("%d", systemInfo.mem_cap);
    return 0;
}