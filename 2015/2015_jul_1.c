#include <stdio.h>

#define MAX_LEN 101

int main(void)
{
    char str[MAX_LEN], *c;
    int n, bc;

    fgets(str, MAX_LEN, stdin);

    for (c = str; *c != '\0'; ++c) {
        if (*c == '[') {
            sscanf(c+1, "%d", &n);
            c += n - 1;
        } else {
            putchar(*c);
        }
    }
}
