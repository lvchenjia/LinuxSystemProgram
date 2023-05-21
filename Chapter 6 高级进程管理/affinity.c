#define _GNU_SOURCE
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>


#include <sched.h>
#include <pthread.h>


//亲合度
//指的是进程或线程在某个CPU上运行的倾向
//因为进程或线程在某个CPU上运行，会有更多的缓存命中，从而提高程序的性能
//int sched_getaffinity(pid_t pid, size_t cpusetsize, cpu_set_t *mask);
//int sched_setaffinity(pid_t pid, size_t cpusetsize, const cpu_set_t *mask);

void sched_getaffinity_test(){
    int ret;
    cpu_set_t mask;
    CPU_ZERO(&mask);
    errno = 0;
    ret = sched_getaffinity(0, sizeof(mask), &mask);
    if (ret == -1 && errno != 0)
        perror("sched_getaffinity error");
    else
        printf("sched_getaffinity value is %d\n", ret);
}

void sched_setaffinity_test(){
    int ret;
    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(0, &mask);
    errno = 0;
    ret = sched_setaffinity(0, sizeof(mask), &mask);
    if (ret == -1 && errno != 0)
        perror("sched_setaffinity error");
    else
        printf("sched_setaffinity value is %d\n", ret);
}

void print(char *str)
{
    printf("\033[1;33m%s\033[0m\n", str);
}

int main(int argc, char *argv[])
{
    print("sched_getaffinity_test");
    sched_getaffinity_test();
    print("sched_setaffinity_test");
    sched_setaffinity_test();
    return 0;
}