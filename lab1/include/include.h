#ifndef SUM_H
#define SUM_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>

int create_processe();
void closeFD(int fd);
void dup2FD(int oldfd, int newfd);

#endif