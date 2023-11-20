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

    char buffer[1];
    ssize_t n;
    while ((n = read(0, buffer, sizeof(buffer))) > 0)
    {
        char upper_array[n];
        for (int i = 0; i < n; i++)
        {
            upper_array[i] = toupper((unsigned char)buffer[i]);
        }
        write(1, upper_array, n);
    }
    if (n < 0)
    {
        perror("read 1");
        exit(EXIT_FAILURE);
    }
    
    closeFD(0);
    closeFD(1);
}