#include <stdbool.h> // bool, true, false
#include <stdio.h>
#include <stdlib.h>

#define PROV_MEM(p) if (!(p)) puts("Neuspesna alokacija"), exit(1)

bool prost(int n)
{
    int i;
    if (n <= 1)
        return false;
    for (i = 2; i <= n/2; i++)
        if (n % i == 0)
            return false;
    return true;
}

void obrada(int **mat, int n)
{
    int i, j;
    for (i = 1; i < n; i++)
        for (j = 1; j < n; j++)
            if (i + j >= n && prost(mat[i][j]))
                mat[i][j] = mat[n-1-j][n-1-i];
}

int main(int argc, char *argv[])
{
    int **mat, n, i, j;

    if (argc != 2)
        return 2;
    n = atoi(argv[1]);

    PROV_MEM(mat = calloc(n, sizeof(int*)));

    for (i = 0; i < n; i++) {
        PROV_MEM(mat[i] = calloc(n, sizeof(int)));
        for (j = 0; j < n; j++)
            scanf("%d", &mat[i][j]);
    }

    obrada(mat, n);

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++)
            printf("%2d ", mat[i][j]);
        putchar('\n');
    }

    for (i = 0; i < n; i++)
        free(mat[i]);
    free(mat);
}
