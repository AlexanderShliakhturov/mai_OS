#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <math.h>
#include <sys/wait.h>


#include <stdio.h>

int count_len_after_child2(char* buffer, int size) {
    char result[1024];
    int i = 0;
    int j = 0;
    while (j < size) {
        if (buffer[j] == ' ' && buffer[j + 1] == ' ') {
            if (buffer[j + 2] != ' ') {
                result[i] = buffer[j + 2];
                i += 1;
                j += 3;
            } else {
                j += 2;
            }
        } else {
            result[i] = buffer[j];
            j += 1;
            i += 1;
        }
    }
    // printf("Result is: %s\n", result);
    return i;
}

int main() {
    char enter[1024];
    int len = read(0, enter, 1024);

    printf("%d\n", count_len_after_child2(enter, len));

    return 0;
}
