#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/inotify.h>

//inotify
// 是一种文件系统监控机制，可以用来监控文件系统的变化
// 通过inotify机制，可以监控文件系统中的以下事件：
// 文件的创建、删除、移动、修改
// 目录的创建、删除、移动、修改
// 符号链接的创建、删除、移动
// 监控点的创建、删除、移动
// 监控点的挂载、卸载
// 文件的读取、写入 等

// int inotify_init(void);
// int inotify_add_watch(int fd, const char* pathname, uint32_t mask);
// int inotify_rm_watch(int fd, int wd);

void inotify_test(){
    //1. 创建一个inotify实例
    int fd = inotify_init();
    if(fd == -1){
        perror("inotify_init error");
        exit(1);
    }

    //2. 添加监控点
    int wd = inotify_add_watch(fd, ".", IN_ALL_EVENTS);
    if(wd == -1){
        perror("inotify_add_watch error");
        exit(1);
    }

    //做些什么事情 比如读取一个文件
    printf("做些什么事情 比如读取一个文件\n");

    //3. 读取事件
    char buf[1024] = {0};
    int ret = read(fd, buf, sizeof(buf));
    if(ret == -1){
        perror("read error");
        exit(1);
    }

    //4. 解析事件
    struct inotify_event* event = (struct inotify_event*)buf;
    printf("mask = %d\n", event->mask);
    printf("name = %s\n", event->name);

    char** mask_str = (char*[]){
        "IN_ACCESS",
        "IN_MODIFY",
        "IN_ATTRIB",
        "IN_CLOSE_WRITE",
        "IN_CLOSE_NOWRITE",
        "IN_OPEN",
        "IN_MOVED_FROM",
        "IN_MOVED_TO",
        "IN_CREATE",
        "IN_DELETE",
        "IN_DELETE_SELF",
        "IN_MOVE_SELF",
        "IN_UNMOUNT",
        "IN_Q_OVERFLOW",
        "IN_IGNORED",
        "IN_CLOSE",
        "IN_MOVE"
    };

    for(int i = 0; i < 17; ++i){
        if(event->mask & (1 << i)){
            printf("event: %s\n", mask_str[i]);
        }
    }


    //5. 删除监控点
    inotify_rm_watch(fd, wd);

    //6. 关闭inotify实例
    close(fd);
}

//yellow
void print(const char* str){
    printf("\033[33m%s\033[0m\n", str);
}

int main(){
    print("inotify test start");
    inotify_test();
    return 0;
}