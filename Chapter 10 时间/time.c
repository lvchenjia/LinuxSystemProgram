#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <time.h>
#include <sys/time.h>
#include <sys/times.h>


//时间
//墙上时间 wall clock time
//进程时间 process time
//单调时间 monotonic time

//相对时间 基于某个时间点的时间
//绝对时间 基于某个固定时间点的时间

//Unix时间戳 从1970年1月1日0时0分0秒到现在的秒数
//typedef long time_t;

//微秒级精度
/*
struct timeval{
    time_t tv_sec; //秒
    suseconds_t tv_usec; //微秒
};
*/

//纳秒级精度
/*
struct timespec{
    time_t tv_sec; //秒
    long tv_nsec; //纳秒
};
*/

//tm
/*
struct tm{
    int tm_sec; //秒
    int tm_min; //分
    int tm_hour; //时
    int tm_mday; //日
    int tm_mon; //月
    int tm_year; //年
    int tm_wday; //星期
    int tm_yday; //一年中的第几天
    int tm_isdst; //夏令时
};

*/

//描述进程时间
//clock_t 表示时钟滴答数 通常是long类型
//CLOCKS_PER_SEC 表示每秒的时钟滴答数

void time_test(){
    time_t t = time(NULL);
    printf("t = %ld\n", t);
    printf("t = %s", ctime(&t));
}

void gettimeofday_test(){
    struct timeval tv;
    gettimeofday(&tv, NULL);
    printf("tv_sec = %ld\n", tv.tv_sec);
    printf("tv_usec = %ld\n", tv.tv_usec);
}

void clock_gettime_test(){
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    printf("tv_sec = %ld\n", ts.tv_sec);
    printf("tv_nsec = %ld\n", ts.tv_nsec);
}

//进程时间
/*
struct tms{
    clock_t tms_utime; //用户CPU时间
    clock_t tms_stime; //系统CPU时间
    clock_t tms_cutime; //子进程用户CPU时间
    clock_t tms_cstime; //子进程系统CPU时间
};
*/

void times_test(){
    struct tms t;
    for(int i = 0; i < 100000000; i++){
        int j = i * i;
    }
    times(&t);

    printf("tms_utime = %ld\n", t.tms_utime);
    printf("tms_stime = %ld\n", t.tms_stime);
    printf("tms_cutime = %ld\n", t.tms_cutime);
    printf("tms_cstime = %ld\n", t.tms_cstime);
}

//usleep 微秒级睡眠
void usleep_test(){
    printf("sleep start\n");
    usleep(500000);
    printf("sleep end\n");
}

//nanosleep 纳秒级睡眠
void nanosleep_test(){
    struct timespec ts;
    ts.tv_sec = 0;
    ts.tv_nsec = 500000000;
    printf("sleep start\n");
    nanosleep(&ts, NULL);
    printf("sleep end\n");
}

//yellow
void print(char* str){
    printf("\033[33m%s\033[0m\n", str);
}

int main(){
    print("time test");
    time_test();
    print("gettimeofday test");
    gettimeofday_test();
    print("clock_gettime test");
    clock_gettime_test();
    print("times test");
    times_test();
    print("usleep test");
    usleep_test();
    print("nanosleep test");
    nanosleep_test();
    
    return 0;
}