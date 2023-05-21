#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

/*

flags: O_RDONLY, O_WRONLY, O_RDWR, O_CREAT, O_EXCL, O_TRUNC, O_APPEND

O_RDONLY: 只读
O_WRONLY: 只写
O_RDWR: 读写
O_CREAT: 文件不存在则创建，存在则打开
O_EXCL: 与O_CREAT同用，若文件存在则报错
O_TRUNC: 打开文件时，将文件长度截断为0
O_APPEND: 写入时，总是追加到文件尾端

权限: S_IRUSR, S_IWUSR, S_IXUSR, S_IRGRP, S_IWGRP, S_IXGRP, S_IROTH, S_IWOTH, S_IXOTH

S_IRUSR: 文件所有者具有读权限
S_IWUSR: 文件所有者具有写权限
S_IXUSR: 文件所有者具有执行权限
S_IRGRP: 用户组具有读权限
S_IWGRP: 用户组具有写权限
S_IXGRP: 用户组具有执行权限
S_IROTH: 其他用户具有读权限
S_IWOTH: 其他用户具有写权限
S_IXOTH: 其他用户具有执行权限

*/

void open_a_not_exist_file()
{
    int fd = open("not_exist_file", O_RDONLY);
    if (fd == -1)
    {
        printf("open: %s\n", strerror(errno));
    }else{
        printf("open success\n");
    }
    close(fd);
}

void create_a_file()
{
    int fd = open("new_file", O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
    //下面两者等价
    //open("new_file", O_CREAT|O_WRONLY|O_TRUNC, 0644);
    //creat("new_file", 0644);
    if (fd == -1)
    {
        printf("create: %s\n", strerror(errno));
    }else{
        printf("create success\n");
    }
    close(fd);
}

void read_a_file()
{
    int fd = open("Text", O_RDONLY);
    if (fd == -1)
    {
        printf("open: %s\n", strerror(errno));
    }else{
        char buf[1024];
        int len = read(fd, buf, sizeof(buf));
        if (len == -1)
        {
            printf("read: %s\n", strerror(errno));
        }else if(len > sizeof(buf)-1){
            printf("read: buf is too small\n");
        }else{
            buf[len] = '\0';
            printf("read success\n");
            printf("%s\n", buf);
        }
    }
    close(fd);
}

void write_a_file(){
    const char text[] = "\nHello World!";
    int fd = open("Text", O_WRONLY | O_APPEND);
    if (fd == -1)
    {
        printf("open: %s\n", strerror(errno));
    }else{
        int len = write(fd, text, strlen(text));
        if (len == -1){
            printf("write: %s\n", strerror(errno));
        }else{
            printf("write success\n");
        }
    }
    close(fd);
}

//fsync
//将文件的修改缓存区数据写入磁盘

//fdatasync
//将文件的修改缓存区数据写入磁盘，但不包括文件属性(元信息 包括文件大小，修改时间等)

//sync
//将所有修改缓存区数据写入磁盘,不是针对某个文件，而是针对所有文件


int main(int argc, char *argv[])
{
    open_a_not_exist_file();
    create_a_file();
    read_a_file();
    write_a_file();
    return 0;
}

