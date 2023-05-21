#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/stat.h>
#include <sys/types.h>

//chmod命令用于修改文件或目录的权限
//int chmod(const char *pathname, mode_t mode);
//int fchmod(int fd, mode_t mode);

void chmod_test(){
    int ret;
    errno = 0;
    ret = chmod("./testfile", 0777);
    if (ret == -1 && errno != 0)
        perror("chmod error");
    else
        printf("chmod success\n");

    //change to 0644
    ret = chmod("./testfile", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (ret == -1 && errno != 0)
        perror("chmod error");
    else
        printf("chmod success\n");
}

void fchmod_test(){
    int ret;
    errno = 0;
    ret = fchmod(0, 0777);
    if (ret == -1 && errno != 0)
        perror("fchmod error");
    else
        printf("fchmod success\n");
}

//chown命令用于修改文件或目录的所有者和所属组
//int chown(const char *pathname, uid_t owner, gid_t group);
//int fchown(int fd, uid_t owner, gid_t group);

void chown_test(){
    int ret;
    errno = 0;
    ret = chown("./testfile", 0, 0);
    if (ret == -1 && errno != 0)
        perror("chown error");
    else
        printf("chown success\n");
}

void fchown_test(){
    int ret;
    errno = 0;
    ret = fchown(0, 0, 0);
    if (ret == -1 && errno != 0)
        perror("fchown error");
    else
        printf("fchown success\n");
}

void print(char* str){
    printf("\033[33m%s\033[0m\n", str);
}

int main(int argc, char* argv[]){
    print("chmod_test");
    chmod_test();
    print("fchmod_test");
    fchmod_test();
    print("chown_test");
    chown_test();
    print("fchown_test");
    fchown_test();
    return 0;
}
