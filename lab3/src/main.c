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

int count_len_after_child2(char *buffer, int size)
{
    char result[1024];
    int i = 0;
    int j = 0;
    while (j < size)
    {
        if (buffer[j] == ' ' && buffer[j + 1] == ' ')
        {
            if (buffer[j + 2] != ' ')
            {
                result[i] = buffer[j + 2];
                i += 1;
                j += 3;
            }
            else
            {
                j += 2;
            }
        }
        else
        {
            result[i] = buffer[j];
            j += 1;
            i += 1;
        }
    }
    // printf("Result is: %s\n", result);
    return i;
}

int main()
{
    const int max_buffer_size = 1024;
    const int count_semafore = 3;

    // Инициализируем семафоры
    char *list_semafore_name[] = {"/semafor0", "/semafor1", "/semafor2"};

    sem_t *list_semafore[count_semafore];

    for (int i = 0; i < count_semafore; ++i)
    {
        if ((list_semafore[i] = sem_open(list_semafore_name[i], O_CREAT, S_IRWXU, 0)) == SEM_FAILED)
        {
            perror("her 2352345234 5e");
        }
    }

    // Создаем файловый дескриптор

    int mmap_file_descriptior;
    char mmap_file_name[] = "/mmap_file";

    // Создаем memory mapped файл, привязанный к дескриптору

    if ((mmap_file_descriptior = shm_open(mmap_file_name, O_CREAT | O_RDWR, S_IRWXU)) == -1)
    {
        perror("open mmap_file_descriptior");
        return -1;
    }

    pid_t child1 = create_processe();

    if (child1 == 0)
    {

        dup2(mmap_file_descriptior, STDIN_FILENO);

        execl("../build/child1", list_semafore_name[0], list_semafore_name[1], NULL);

        perror("child1");
        exit(EXIT_FAILURE);
    }

    pid_t child2 = create_processe();

    if (child2 == 0)
    {

        dup2(mmap_file_descriptior, STDIN_FILENO);
        execl("../build/child2", list_semafore_name[1], list_semafore_name[2], NULL);

        perror("child2");
        exit(EXIT_FAILURE);
    }

    char input_buffer[max_buffer_size];

    char enter[20] = "Enter a string: \n";

    write(1, enter, 20);

    char string[max_buffer_size];

    int count;

    char *mp;
    while ((count = read(0, string, max_buffer_size)) > 0)
    {
        // Установка размера memory-mapped файла
        if (ftruncate(mmap_file_descriptior, count) == -1)
        {
            perror("Could not set size of mfile.txt");
            return 1;
        }

        // mp - указатель на начало отображенной области
        if ((mp = mmap(NULL, count, PROT_READ | PROT_WRITE, MAP_SHARED, mmap_file_descriptior, 0)) == MAP_FAILED)
        {
            perror("mmap");
            return -1;
        }
        for (int i = 0; i < count; ++i)
        {
            mp[i] = string[i];
        }

        // printf("Даём команду первому ребенку\n");
        fflush(stdout);

        if (sem_post(list_semafore[0]) == -1)
        {
            perror("here");
        }

        // printf("Ждём команду от второго ребенка\n");
        fflush(stdout);

        sem_wait(list_semafore[2]);

        // printf("Получили команду от второго ребенка\n");
        fflush(stdout);

        int len_after_child2 = count_len_after_child2(string, count);

        char result_buffer[max_buffer_size];

        for (int i = 0; i <= len_after_child2; i++)
        {
            result_buffer[i] = mp[i];
        }

        printf("Печатаю результат:\n");
        printf("%s\n", result_buffer);
    }

    unlink(mmap_file_name);

    if (kill(child1, SIGTERM) == -1)
    {
        perror("Ошибка при отправке сигнала");
    }

    if (kill(child2, SIGTERM) == -1)
    {
        perror("Ошибка при отправке сигнала");
    }

    for (int i = 0; i < count_semafore; ++i)
    {
        sem_close(list_semafore[i]);
        sem_unlink(list_semafore_name[i]);
    }

    return 0;
}