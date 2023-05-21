#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include <sys/types.h>
#include <sys/wait.h>

//wait for child process to exit
void wait_test()
{
    int status;
    pid_t pid;
    pid = fork();
    if (pid < 0)
    {
        perror("fork error");
        return;
    }
    else if (pid == 0)
    {
        printf("child process\n");
        sleep(1);
        //kill(getpid(), SIGSTOP);
        abort();
        //exit(6);
    }
    else
    {
        // 父进程
        printf("parent process\n");
        wait(&status);
        if (WIFEXITED(status))
        {
            printf("child process exit with %d\n", WEXITSTATUS(status));
        }
        else if (WIFSIGNALED(status))
        {
            printf("killed by signal=%d%s\n", WTERMSIG(status),
                   WCOREDUMP(status) ? "(core file generated)" : "");
        }
        else if (WIFSTOPPED(status))
        {
            printf("stopped by signal=%d\n", WSTOPSIG(status));
        }
        else if (WIFCONTINUED(status))
        {
            printf("continued\n");
        }
    }
}

void print(char *str)
{
    printf("\033[1;33m%s\033[0m\n", str);
}

int main(int argc, char *argv[])
{
    print("wait test");
    wait_test();
    return 0;
}