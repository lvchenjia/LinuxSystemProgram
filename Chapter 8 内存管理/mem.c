#define _GNU_SOURCE
//这个宏的作用是告诉编译器，我们要使用GNU的库函数，这样就可以使用GNU的库函数了
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/mman.h>

//memset 将一段内存设置为某个值 按字节设置
void memset_test(){
    char str[10];
    memset(str, 'a', 10);
    printf("str = %s\n", str);
}

//memcpy 内存拷贝
void memcpy_test(){
    char str1[10] = "hello";
    char str2[10] = {0};
    memcpy(str2, str1, 5);
    printf("str2 = %s\n", str2);
}

//memmove 内存拷贝
void memmove_test(){
    char str1[10] = "hello";
    memmove(str1 + 2, str1, 5);
    printf("str1 = %s\n", str1);
}

//memcmp 内存比较
void memcmp_test(){
    char str1[10] = "hello";
    char str2[10] = "hello";
    int ret = memcmp(str1, str2, 5);
    if(ret == 0){
        printf("str1 == str2\n");
    }else if(ret > 0){
        printf("str1 > str2\n");
    }else{
        printf("str1 < str2\n");
    }
}

//memchr 内存查找
void memchr_test(){
    char str[10] = "hello";
    char* ret = memchr(str, 'l', 5);
    if(ret == NULL){
        printf("not found\n");
    }else{
        printf("founded at %ld\n", ret - str);
    }
}

//memfrob 内存加密
//memfrob 会将内存中的每个字节与 0x2A 做异或运算
void memfrob_test(){
    char str[10] = "hello";
    memfrob(str, 5);
    printf("str = %s\n", str);
    memfrob(str, 5);
    printf("str = %s\n", str);
}


//mlock
//mlock 用来锁定一段内存，使其不能被交换到磁盘上
//int mlock(const void* addr, size_t len);
void mlock_test(){
    char* str = (char*)malloc(10);
    strcpy(str, "hello");
    mlock(str, 10);
    printf("str = %s\n", str);
    munlock(str, 10);
    free(str);
}

//mlockall
//mlockall 用来锁定整个进程的内存空间
//int mlockall(int flags);
void mlockall_test(){
    char* str = (char*)malloc(10);
    strcpy(str, "hello");
    mlockall(MCL_CURRENT);
    printf("str = %s\n", str);
    munlockall();
    free(str);
}

void print(const char* str){
    printf("\033[33m%s\033[0m\n", str);
}

int main(){
    print("memset test");
    memset_test();
    print("memcpy test");
    memcpy_test();
    print("memmove test");
    memmove_test();
    print("memcmp test");
    memcmp_test();
    print("memchr test");
    memchr_test();
    print("memfrob test");
    memfrob_test();
    return 0;
}