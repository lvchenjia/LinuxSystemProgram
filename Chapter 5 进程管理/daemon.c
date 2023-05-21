#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// 守护进程
// 什么是守护进程？
// 守护进程是一种生存期较长的进程
//它独立于控制终端并且周期性地执行某种任务或等待处理某些发生的事件。

int main()
{
    pid_t pid;
    int i;

    // 创建子进程
    pid = fork();

    // 创建子进程失败
    if (pid < 0)
    {
        perror("fork error");
        exit(1);
    }

    // 父进程退出
    if (pid > 0)
    {
        exit(0);
    }

    // 子进程继续执行
    // 创建新的会话，子进程成为会话的首进程
    setsid();

    // 改变当前工作目录到根目录
    chdir("/");

    // 重设文件权限掩码
    umask(0);

    // 关闭文件描述符
    for (i = 0; i < 3; i++)
    {
        close(i);
    }

    // 守护进程工作
    while (1)
    {
        sleep(1);
    }

    return 0;
}
