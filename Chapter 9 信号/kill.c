#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

//kill
//kill可以用来向进程发送信号
void kill_test(){
    pid_t pid = fork();
    if(pid == -1){
        perror("fork error");
        exit(1);
    }
    if(pid == 0){
        //子进程
        while(1){
            printf("I am child process, pid = %d\n", getpid());
            sleep(1);
        }
    }
    else{
        //父进程
        sleep(3);
        printf("kill child process, pid = %d\n", pid);
        kill(pid, SIGKILL);
        printf("killed\n");
    }
}

//killpg 
//killpg可以用来向进程组发送信号
//killpg(pgrp, sig) <=> kill(-pgrp, sig)

//raise
//raise可以用来向自己发送信号
void raise_test(){
    raise(SIGKILL);
}

//abort
//abort可以用来向自己发送SIGABRT信号

//重入
//可重入函数是指在多线程环境下，可以被多个线程安全调用的函数

//yellow
void print(char* str){
    printf("\033[33m%s\033[0m\n", str);
}

int main(){
    print("kill test");
    kill_test();
    print("raise test");
    raise_test();
    return 0;
}