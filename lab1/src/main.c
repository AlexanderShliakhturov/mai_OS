#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "../include/include.h"

int main()
{
    const int max_size_buff = 1024;

    int pipe1[2];
    int pipe2[2];

    if (pipe(pipe1) == -1 || pipe(pipe2) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t child1 = create_processe();

    if (child1 == 0)
    {

        closeFD(pipe1[1]);
        closeFD(pipe2[0]);

        dup2FD(pipe1[0], 0);
        dup2FD(pipe2[1], 1);

        execl("../build/child1", " ", NULL);

        perror("child1");
        exit(EXIT_FAILURE);
    }

    int pipe3[2];
    if (pipe(pipe3) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t child2 = create_processe();

    if (child2 == 0)
    {
        closeFD(pipe1[1]);
        closeFD(pipe1[0]);

        closeFD(pipe2[1]);
        closeFD(pipe3[0]);

        dup2FD(pipe2[0], 0);
        dup2FD(pipe3[1], 1);
        execl("../build/child2", " ", NULL);

        perror("child2");
        exit(EXIT_FAILURE);
    }

    closeFD(pipe1[0]);
    closeFD(pipe2[0]);
    closeFD(pipe2[1]);
    closeFD(pipe3[1]);

    char input_buffer[max_size_buff];

    char enter[20] = "Enter a string: \n";

    int x = write(1, enter, 30);

    // printf("записали врайтом симоволов: %d\n", x);

    // for(int i = 15; i <= 29; i++){
    //     printf("HERE %d\n", enter[i]);
    // }
    

    ssize_t size;
    while ((size = read(0, input_buffer, max_size_buff)) > 0)
    {
        write(pipe1[1], input_buffer, size);
    }

    if (size < 0)
    {
        perror("read 1");
        exit(EXIT_FAILURE);
    }

    closeFD(pipe1[1]);

    char result_buffer[max_size_buff];
    ssize_t n;

    char result[20] = "Result: \n";

    write(1, result, 20);

    
    while ((n = read(pipe3[0], result_buffer, sizeof(result_buffer))) > 0)
    {
        write(1, result_buffer, n);
    }

    if (n < 0)
    {
        perror("read 2");
        exit(EXIT_FAILURE);
    }

    closeFD(pipe3[0]);

    return 0;
}