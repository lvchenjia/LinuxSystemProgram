#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

//用户id uid
//root uid = 0
//uid可以通过/etc/passwd文件查看
//gid可以通过/etc/group文件查看

void uid_test()
{
    printf("uid=%d, euid=%d\n", getuid(), geteuid());
}

void gid_test()
{
    printf("gid=%d, egid=%d\n", getgid(), getegid());
}

//setuid
void setuid_test()
{
    uid_t uid = getuid();
    uid = 1001;
    printf("uid=%d, euid=%d\n", getuid(), geteuid());
    if (setuid(uid) < 0)
    {
        perror("setuid error");
        return;
    }
    printf("uid=%d, euid=%d\n", getuid(), geteuid());
}

//yellow
void print(char *str)
{
    printf("\033[1;33m%s\033[0m\n", str);
}

int main(int argc, char *argv[])
{
    //uid_test();
    //gid_test();
    setuid_test();
    return 0;
}