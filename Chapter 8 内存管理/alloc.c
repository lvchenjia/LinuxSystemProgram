#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <malloc.h>
#include <alloca.h>

//基本内存结构
//low address
//.text 代码段
//.data 数据段
//.bss 未初始化数据段
//heap 堆
//stack 栈
//high address

//malloc
void* xmalloc(size_t size){
    void* ptr = malloc(size);
    if(ptr == NULL){
        perror("xmalloc");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

//calloc
//calloc和malloc的区别在于，calloc会将分配的内存初始化为0
//实际使用中calloc可能比malloc and memset更高效
//因为calloc可能会直接从操作系统的已清零的内存池中分配内存
void* xcalloc(size_t nmemb, size_t size){
    void* ptr = calloc(nmemb, size);
    if(ptr == NULL){
        perror("xcalloc");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

//realloc
//realloc可以用来调整之前分配的内存的大小

//free
//malloc, calloc, realloc分配的内存，都需要使用free来释放

//alloca
//以上的函数都是在堆上分配内存，alloca是在栈上分配内存
//由于栈的特性，alloca分配的内存会在函数返回时自动释放
//alloca可能导致栈溢出，所以不推荐使用

int main(){
    void* p = malloc(10240);
    malloc_stats();
    free(p);

    //ulimit -a 查看系统默认的栈大小
    //默认的栈大小是8192KB
    //char arr[1024*1024*8]; 爆栈
    //ulimit -s 16384 设置栈大小为16384KB

    char arr[1024*1024*8];

    size_t one_million = 1024 * 1024;
    //void *q = alloca(one_million*7);
    malloc_stats();
    return 0;
}