#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

//signal
/*
Linux系统支持的信号
信号		默认动作		说明
SIGHUP		terminate		终端挂起或者控制进程终止
SIGINT		terminate		键盘中断
SIGQUIT		core dump		键盘退出
SIGILL		core dump		非法指令
SIGABRT		core dump		异常终止
SIGFPE		core dump		浮点异常
SIGKILL		terminate		强制终止
SIGSEGV		core dump		无效内存引用
SIGPIPE		terminate		管道破裂
SIGALRM		terminate		定时器超时
SIGTERM		terminate		终止
SIGUSR1		terminate		用户自定义信号1
SIGUSR2		terminate		用户自定义信号2
SIGCHLD		ignore			子进程状态改变
SIGCONT		ignore			继续执行一个停止的进程
SIGSTOP		stop			停止进程
SIGTSTP		stop			键盘停止
SIGTTIN		stop			后台进程读终端
SIGTTOU		stop			后台进程写终端
*/



//signal
//signal可以用来设置信号的处理函数
//pause可以用来挂起进程，直到有信号来了才会返回


void signal_handler(int signo){
    psignal(signo, "Caught");
    exit(0);
}

void signal_test(){
    signal(SIGINT, signal_handler);
    while(1){
        pause();
    }
}

//yellow
void print(char* str){
    printf("\033[33m%s\033[0m\n", str);
}

int main(){
    print("signal test");
    signal_test();
    return 0;
}