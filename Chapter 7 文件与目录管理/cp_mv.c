//copy and move
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

//复制 Linux不提供多个文件复制的系统调用，只能自己实现

//移动
//int rename(const char* oldpath, const char* newpath);

void rename_test(){
    int ret = rename("test_folder1", "test_folder2");
    if(ret == -1){
        perror("rename error");
        exit(1);
    }
}


unsigned long long get_a_rand(){
    //read from /dev/random

    int fd = open("/dev/random", O_RDONLY);
    if(fd == -1){
        perror("open error");
        exit(1);
    }

    unsigned long long rand_num = 0;
    int ret = read(fd, &rand_num, sizeof(rand_num));
    if(ret == -1){
        perror("read error");
        exit(1);
    }

    close(fd);
    return rand_num;
}


void print(const char* str){
    printf("\033[33m%s\033[0m\n", str);
}

int main(){
    //print("rename test start");
    //rename_test();

    print("get a rand num");
    unsigned long long rand_num = get_a_rand();
    printf("rand_num = %llu\n", rand_num);
    return 0;
}

//设备节点
// /dev/null 空设备
// /dev/zero 零设备
// /dev/full 满设备
// /dev/random 随机设备
// /dev/urandom 伪随机设备
// /dev/tty 终端设备
// /dev/sda 硬盘设备
// /dev/psaux 鼠标设备
// /dev/fb0 显卡设备

