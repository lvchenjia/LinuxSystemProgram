#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include <linux/ioprio.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <sys/syscall.h>


//nice命令用于修改程序的调度优先级
//nice命令的调度优先级范围是-20~19
//默认情况下，nice命令的调度优先级为0
//nice命令的调度优先级越高，程序的调度优先级越低

void nice_test(){
    int ret;
    errno = 0;
    ret = nice(10);
    if (ret == -1 && errno != 0)
        perror("nice error");
    else
        printf("nice value is %d\n", ret);
}

//getpriority()用来取得某个进程组的优先顺序值
//setpriority()用来设置某个进程组的优先顺序值

void getpriority_test(){
    int ret;
    errno = 0;
    ret = getpriority(PRIO_PROCESS, 0);
    if (ret == -1 && errno != 0)
        perror("getpriority error");
    else
        printf("nice value is %d\n", ret);
}

void setpriority_test(){
    int ret;
    errno = 0;
    ret = setpriority(PRIO_PROCESS, 0, 10);
    if (ret == -1 && errno != 0)
        perror("setpriority error");
    else
        printf("nice value is %d\n", ret);
}

//io优先级
//int ioprio_get(int which, int who);
//int ioprio_set(int which, int who, int ioprio);

void ioprio_get_test(){
    int ret;
    errno = 0;
    //syscall
    ret = syscall(SYS_ioprio_get, IOPRIO_WHO_PROCESS, 0);
    if (ret == -1 && errno != 0)
        perror("ioprio_get error");
    else
        printf("nice value is %d\n", ret);
}

void ioprio_set_test(){
    int ret;
    errno = 0;
    ret = syscall(SYS_ioprio_set, IOPRIO_WHO_PROCESS, 0, 0);
    if (ret == -1 && errno != 0)
        perror("ioprio_set error");
    else
        printf("nice value is %d\n", ret);
}

void print(char* str){
    printf("\033[1;33m%s\033[0m", str);
}

int main(){
    //get nice
    print("get nice\n");
    printf("nice value is %d\n", nice(0));
    print("nice test\n");
    nice_test();
    print("getpriority test\n");
    getpriority_test();
    print("setpriority test\n");
    setpriority_test();
    print("ioprio_get test\n");
    ioprio_get_test();
    print("ioprio_set test\n");
    ioprio_set_test();
    return 0;
}