#include <stdio.h>
#include <stdlib.h>

#define STR_LEN 101

int main(void)
{
    char str[STR_LEN], *c;
    int n, bc;

    fgets(str, STR_LEN, stdin);

    for (c = str; *c; ++c) {
        if (*c == '[') {
            n = atoi(c+1);
            c += n - 1;
        } else {
            putchar(*c);
        }
    }
}
