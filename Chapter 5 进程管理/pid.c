#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include <sys/wait.h>

// pid 进程ID
// ppid 父进程ID

void pid_test()
{
    pid_t pid;
    pid = getpid();
    printf("pid = %d\n", pid);
    pid = getppid();
    printf("ppid = %d\n", pid);
}

// exec 系列函数
// exec函数族是用来执行一个新的程序的
// execl，execlp，execle，execv，execvp，execvpe
// 带有p在环境变量PATH中查找可执行文件，带有e需要传递环境变量
// l表示参数以列表的形式传递，v表示参数以数组的形式传递

void exec_test()
{
    pid_t pid;
    pid = fork();
    if (pid < 0)
    {
        perror("fork error");
        return;
    }
    else if (pid == 0)
    {
        execl("/bin/ls", "ls", "-l", NULL);
    }
    else
    {
        // 父进程
        wait(NULL);
    }
}

// atexit
// 注册一个函数，当进程正常退出时，调用该函数
// 注册的函数按照栈的方式存储，先注册的后调用

void on_exit_func1() { printf("on_exit_func1\n"); }

void on_exit_func2() { printf("on_exit_func2\n"); }

void atexit_test()
{
    atexit(on_exit_func1);
    atexit(on_exit_func2);
}

void print(char *str)
{
    printf("\033[1;33m%s\033[0m\n", str);
}

int main()
{
    print("pid test");
    pid_test();
    print("exec test");
    exec_test();
    print("atexit test");
    atexit_test();
    return 0;
}