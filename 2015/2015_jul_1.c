#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 101

int main(void)
{
    char str[MAX_LEN], *c;
    int n, bc;

    fgets(str, MAX_LEN, stdin);

    for (c = str; *c; ++c) {
        if (*c == '[') {
            n = atoi(c+1);
            c += n - 1;
        } else {
            putchar(*c);
        }
    }
}
