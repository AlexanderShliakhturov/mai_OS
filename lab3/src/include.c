#include "../include/include.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>

int create_processe()
{
    pid_t pid = fork();
    if (pid < 0)
    {
        perror("Creating a process");
        exit(EXIT_FAILURE);
    }

    return pid;
}

void closeFD(int fd)
{

    if (close(fd) == -1)
    {
        perror("Closing FD");
        exit(EXIT_FAILURE);
    }
}

void dup2FD(int oldfd, int newfd)
{
    if (dup2(oldfd, newfd) == -1)
    {
        perror("DUP2");
        exit(EXIT_FAILURE);
    }
}

