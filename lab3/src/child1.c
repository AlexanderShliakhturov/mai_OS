#include <sys/stat.h>
#include "stdio.h"
#include "stdlib.h"
#include <fcntl.h>
#include "unistd.h"
#include "sys/wait.h"
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <signal.h>
#include "../include/include.h"

#include "../include/include.h"

sem_t *child_list_semafor[2];

void handle_sigterm()
{
    for (int i = 0; i < 2; ++i)
    {
        close(i);
        sem_close(child_list_semafor[i]);
    }
    exit(0);
}

int main(int argc, char *argv[])
{
    fflush(stdout);
    for (int i = 0; i < 2; ++i)
    {
        // printf("%s\n", argv[i]);
        child_list_semafor[i] = sem_open(argv[i], O_CREAT);
    }

    struct stat sd;

    while (1)
    {
        // printf("Ждем команду от родителя\n");
        fflush(stdout);

        sem_wait(child_list_semafor[0]);

        // printf("Получили команду от родителя\n");
        fflush(stdout);

        if (signal(SIGTERM, handle_sigterm) == SIG_ERR)
        {
            perror("Error while setting a signal handler");
            return EXIT_FAILURE;
        }

        // читаем из shared memory, перенаправленного в STDIN
        if (fstat(STDIN_FILENO, &sd) == -1)
        {
            perror("could not get file size. \n");
        }

        char *mp = mmap(NULL, sd.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, STDIN_FILENO, 0);

        for (int i = 0; i < sd.st_size; ++i)
        {
            mp[i] = toupper(mp[i]);
        }

        // printf("Даём команду второму ребенку\n");
        sem_post(child_list_semafor[1]);
    }
}