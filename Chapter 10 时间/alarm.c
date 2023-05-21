#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <sys/times.h>


//alarm
void alarm_handler(int signo){
    printf("alarm\n");
}

void alarm_test(){
    //1. 注册信号捕捉函数
    signal(SIGALRM, alarm_handler);

    //2. 设置闹钟
    alarm(2);

    //3. 模拟做一些事情
    int i = 0;
    for(i = 0; i < 5; ++i){
        printf("i = %d\n", i);
        sleep(1);
    }
}


//timer 
void timer_handler(int signo){
    printf("timer\n");
}

void timer_test(){
    //1. 创建一个定时器
    struct itimerval new_value;
    new_value.it_value.tv_sec = 2;
    new_value.it_value.tv_usec = 0;
    new_value.it_interval.tv_sec = 1;
    new_value.it_interval.tv_usec = 0;

    setitimer(ITIMER_REAL, &new_value, NULL);

    //2. 注册信号捕捉函数
    signal(SIGALRM, timer_handler);

    //3. 模拟做一些事情
    int i = 0;
    for(i = 0; i < 5; ++i){
        printf("i = %d\n", i);
        sleep(1);
    }
}

//yellow
void print(char* str){
    printf("\033[33m%s\033[0m\n", str);
}

int main(){
    print("alarm test");
    alarm_test();
    print("timer test");
    timer_test();
    return 0;
}