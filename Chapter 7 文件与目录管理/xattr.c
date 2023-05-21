#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/stat.h>
#include <sys/types.h>

//xattr命令用于修改文件或目录的扩展属性
//int setxattr(const char *path, const char *name, const void *value, size_t size, int flags);


void setxattr_test(){
    int ret;
    errno = 0;
    ret = setxattr("./testfile", "user.test", "test", 4, 0);
    if (ret == -1 && errno != 0)
        perror("setxattr error");
    else
        printf("setxattr success\n");
}

void getxattr_test(){
    int ret;
    char buf[1024];
    errno = 0;
    ret = getxattr("./testfile", "user.test", buf, 1024);
    if (ret == -1 && errno != 0)
        perror("getxattr error");
    else
        printf("the value of user.test is %s\n", buf);
}

void listxattr_test(){
    int ret;
    char buf[1024];
    errno = 0;
    ret = listxattr("./testfile", buf, 1024);
    if (ret == -1 && errno != 0)
        perror("listxattr error");
    else
    {
        printf("the list of xattr is %s\n", buf);
        printf("the length of list is %d\n", ret);
    }
}

void removexattr_test(){
    int ret;
    errno = 0;
    ret = removexattr("./testfile", "user.test");
    if (ret == -1 && errno != 0)
        perror("removexattr error");
    else
        printf("removexattr success\n");
}

void print(char* str){
    printf("\033[33m%s\033[0m\n", str);
}

int main(int argc, char* argv[]){
    print("setxattr_test");
    setxattr_test();
    print("getxattr_test");
    getxattr_test();
    print("listxattr_test");
    listxattr_test();
    print("removexattr_test");
    removexattr_test();
    return 0;
}
