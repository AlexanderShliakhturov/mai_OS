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
    char buffer[1024];
    ssize_t n;
    while ((n = read(0, buffer, sizeof(buffer))) > 0)
    {
        char result[1024];
        int i = 0;
        int j = 0;
        while (j < n)
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
        write(1, result, i + 1);
    }

    if (n < 0) {
        perror("read 1");
        exit(EXIT_FAILURE);
    }
    
    closeFD(0);
    closeFD(1);
}
