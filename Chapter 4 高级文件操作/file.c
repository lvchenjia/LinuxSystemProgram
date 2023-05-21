#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#include <sys/uio.h>
#include <sys/epoll.h>
#include <sys/mman.h>

// 散布I/O
// 散布  允许单次操作多个缓冲区

void writev_test()
{
    struct iovec iov[3];
    ssize_t nr;
    int fd, i;

    char *buf[] = {
        "The term buccaneer comes from the word boucan.\n",
        "A boucan is a wooden frame used for cooking meat.\n",
        "Buccaneer is the West Indies name for a pirate.\n"};

    fd = open("buccaneer.txt", O_WRONLY | O_CREAT | O_TRUNC);
    if (fd == -1)
    {
        perror("open");
        return;
    }

    /* fill out three iovec structures */
    for (i = 0; i < 3; i++)
    {
        iov[i].iov_base = buf[i];
        iov[i].iov_len = strlen(buf[i]) + 1;
    }

    /* with a single call, write them all out */
    nr = writev(fd, iov, 3);
    if (nr == -1)
    {
        perror("writev");
        return;
    }
    printf("wrote %ld bytes\n", nr);

    if (close(fd))
    {
        perror("close");
        return;
    }
}

void readv_test()
{
    char foo[48], bar[51], baz[49];
    struct iovec iov[3];
    ssize_t nr;

    int fd = open("buccaneer.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("open");
        return;
    }

    iov[0].iov_base = foo;
    iov[0].iov_len = sizeof(foo);
    iov[1].iov_base = bar;
    iov[1].iov_len = sizeof(bar);
    iov[2].iov_base = baz;
    iov[2].iov_len = sizeof(baz);

    nr = readv(fd, iov, 3);
    if (nr == -1)
    {
        perror("readv");
        return;
    }
    for (int i = 0; i < 3; i++)
    {
        printf("%d: %s", i, (char *)iov[i].iov_base);
    }
    if (close(fd))
    {
        perror("close");
        return;
    }
}

// epoll
// 用于高效的I/O复用
// epoll_create
// epoll_ctl
// epoll_wait

/*
event:
0: EPOLLIN
1: EPOLLOUT
2: EPOLLERR
3: EPOLLHUP
4: EPOLLRDHUP
5: EPOLLONESHOT
6: EPOLLET
*/

void epoll_test()
{
    int epoll_fd = epoll_create(10);
    if (epoll_fd == -1)
    {
        perror("epoll_create");
        return;
    }
    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = 0;
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, 0, &ev) == -1)
    {
        perror("epoll_ctl");
        return;
    }
    struct epoll_event events[10];
    int nr = epoll_wait(epoll_fd, events, 10, -1);

    //触发epoll_wait后 清除stdin的内容
    char buf[10];
    read(0, buf, 10);

    if (nr == -1)
    {
        perror("epoll_wait");
        return;
    }
    for (int i = 0; i < nr; i++)
    {
        printf("fd = %d, events = %d\n", events[i].data.fd, events[i].events);
    }
}

//存储映射
// mmap     创建存储映射区
// munmap   释放存储映射区
// msync    同步存储映射区
// mprotect 保护存储映射区

void mmap_test()
{
    int fd = open("buccaneer.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("open");
        return;
    }
    char *addr = mmap(NULL, 100, PROT_READ, MAP_PRIVATE, fd, 0);
    if (addr == MAP_FAILED)
    {
        perror("mmap");
        return;
    }
    printf("%s", addr);
    if (munmap(addr, 100) == -1)
    {
        perror("munmap");
        return;
    }
    if (close(fd))
    {
        perror("close");
        return;
    }
}

//yello color
void print(char *str)
{
    printf("\033[1;33m%s\033[0m\n", str);
}

int main(int argc, char *argv[])
{
    print("writev_test");
    writev_test();
    print("readv_test");
    readv_test();
    print("epoll_test");
    epoll_test();
    print("mmap_test");
    mmap_test();
    return 0;
}