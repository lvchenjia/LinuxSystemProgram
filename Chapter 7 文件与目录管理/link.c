//link 链接
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// int link(const char* oldpath, const char* newpath);
// int unlink(const char* pathname);
// int symlink(const char* oldpath, const char* newpath);
// int readlink(const char* pathname, char* buf, size_t bufsize);
//硬链接 link 与原文件共享inode，文件内容相同，文件名不同
//软链接 symlink 与原文件不共享inode，文件内容不同，文件名不同

void link_test(){
    int ret = link("./test_folder1", "./");
    if(ret == -1){
        perror("link error");
        exit(1);
    }
}

void unlink_test(){
    int ret = unlink("test_link");
    if(ret == -1){
        perror("unlink error");
        exit(1);
    }
}

void print(const char* str){
    printf("\033[33m%s\033[0m\n", str);
}

int main(){
    print("link test start");
    link_test();
    print("unlink test start");
    unlink_test();
    return 0;
}