#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/stat.h>
#include <sys/types.h>

//stat 全拼为statue，表示状态的意思
//stat函数用来获取文件的状态信息
//int stat(const char *pathname, struct stat *statbuf);
//int fstat(int fd, struct stat *statbuf);
//int lstat(const char *pathname, struct stat *statbuf);

//lstat函数与stat函数类似，不同之处在于
//当命名的文件是一个符号链接时，lstat返回该符号链接的信息，而不是该符号链接所指向的文件的信息。

/*
struct stat {
    dev_t     st_dev;         // ID of device containing file 
    ino_t     st_ino;         // inode number 
    mode_t    st_mode;        // protection 
    nlink_t   st_nlink;       // number of hard links 
    uid_t     st_uid;         // user ID of owner 
    gid_t     st_gid;         // group ID of owner 
    dev_t     st_rdev;        // device ID (if special file) 
    off_t     st_size;        // total size, in bytes 
    blksize_t st_blksize;     // blocksize for filesystem I/O 
    blkcnt_t  st_blocks;      // number of 512B blocks allocated 
    time_t    st_atime;       // time of last access 
    time_t    st_mtime;       // time of last modification 
    time_t    st_ctime;       // time of last status change 
};
*/

void print_stat(struct stat *statbuf){
    printf("statbuf.st_dev = %ld\n", statbuf->st_dev);
    printf("statbuf.st_ino = %ld\n", statbuf->st_ino);
    printf("statbuf.st_mode = %d\n", statbuf->st_mode);
    printf("statbuf.st_nlink = %ld\n", statbuf->st_nlink);
    printf("statbuf.st_uid = %d\n", statbuf->st_uid);
    printf("statbuf.st_gid = %d\n", statbuf->st_gid);
    printf("statbuf.st_rdev = %ld\n", statbuf->st_rdev);
    printf("statbuf.st_size = %ld\n", statbuf->st_size);
    printf("statbuf.st_blksize = %ld\n", statbuf->st_blksize);
    printf("statbuf.st_blocks = %ld\n", statbuf->st_blocks);
    printf("statbuf.st_atime = %ld\n", statbuf->st_atime);
    printf("statbuf.st_mtime = %ld\n", statbuf->st_mtime);
    printf("statbuf.st_ctime = %ld\n", statbuf->st_ctime);
}

void stat_test(){
    int ret;
    struct stat statbuf;
    errno = 0;
    ret = stat("/etc/passwd", &statbuf);
    if (ret == -1 && errno != 0)
        perror("stat error");
    else
    {
        printf("The file /etc/passwd stat info:\n");
        print_stat(&statbuf);
    }
        
}

void fstat_test(){
    int ret;
    struct stat statbuf;
    errno = 0;
    ret = fstat(0, &statbuf);
    if (ret == -1 && errno != 0)
        perror("fstat error");
    else
    {
        printf("The stat info of fd 0:\n");
        print_stat(&statbuf);
    }
}

void lstat_test(){
    int ret;
    struct stat statbuf;
    errno = 0;
    ret = lstat("/etc/passwd", &statbuf);
    if (ret == -1 && errno != 0)
        perror("lstat error");
    else
    {
        printf("The file /etc/passwd lstat info:\n");
        print_stat(&statbuf);
    }
}

void print(char* str){
    printf("\033[33m%s\033[0m\n", str);
}

int main(int argc, char* argv[]){
    print("stat_test");
    stat_test();
    print("fstat_test");
    fstat_test();
    // print("lstat_test");
    // lstat_test();
    return 0;
}
