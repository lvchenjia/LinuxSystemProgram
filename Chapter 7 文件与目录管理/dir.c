//目录相关操作
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

void print_r(const char* str){
    printf("\033[31m%s\033[0m\n", str);
}

void print_g(const char* str){
    printf("\033[32m%s\033[0m\n", str);
}

void print_y(const char* str){
    printf("\033[33m%s\033[0m\n", str);
}

void print_b(const char* str){
    printf("\033[34m%s\033[0m\n", str);
}

void print_p(const char* str){
    printf("\033[35m%s\033[0m\n", str);
}

//cwd current working directory 当前工作目录
//getcwd()获取当前工作目录
//chdir()改变当前工作目录
//mkdir()创建目录
//rmdir()删除目录
//opendir()打开目录
//readdir()读取目录
//closedir()关闭目录

void getcwd_test(){
    char buf[1024];
    getcwd(buf, sizeof(buf));
    printf("cwd: %s\n", buf);
}

void chdir_test(){
    int ret = chdir("/home/horse/桌面");
    if(ret == -1){
        perror("chdir error");
        exit(1);
    }
    char buf[1024];
    getcwd(buf, sizeof(buf));
    printf("cwd: %s\n", buf);
}

void mkdir_test(){
    int ret = mkdir("test", 0777);
    if(ret == -1){
        perror("mkdir error");
        exit(1);
    }else{
        printf("mkdir success\n");
    }
}

void rmdir_test(){
    int ret = rmdir("test");
    if(ret == -1){
        perror("rmdir error");
        exit(1);
    }else{
        printf("rmdir success\n");
    }
}

void opendir_test(){
    DIR* dir = opendir("/home/horse/桌面");
    if(dir == NULL){
        perror("opendir error");
        exit(1);
    }
    struct dirent* ptr = NULL;
    while((ptr = readdir(dir)) != NULL){
        switch (ptr->d_type)
        {
        case DT_REG:
            printf("%s\n", ptr->d_name);
            break;
        case DT_DIR:
            print_g(ptr->d_name);
            break;
        case DT_LNK:
            print_y(ptr->d_name);
            break;
        default:
            print_r(ptr->d_name);
            break;
        }
    }
    closedir(dir);
}


void print(char* str){
    printf("\033[33m%s\033[0m\n", str);
}

int main(){
    print("getcwd_test");
    getcwd_test();
    print("chdir_test");
    chdir_test();
    print("mkdir_test");
    mkdir_test();
    print("rmdir_test");
    rmdir_test();
    print("opendir_test");
    opendir_test();
    return 0;
}