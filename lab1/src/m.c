#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){

char string1[5] = "0123";
char string2[5] = "5678";

write(1, string1, 10);

}