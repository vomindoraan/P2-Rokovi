#include <stdio.h>
#include <stdlib.h>

#define ALLOC_CHECK(p) if (!(p)) printf("Neuspesna alokacija\n"), exit(1)

int is_prime(int n)
{
    int i, prime = 1;
    if (n <= 1) {
        prime = 0;
    }
    for (i = 2; prime && i <= n/2; ++i) {
        if (n % i == 0) {
            prime = 0;
        }
    }
    return prime;
}

void modify(int **mat, int n)
{
    int i, j;
    for (i = 1; i < n; ++i) {
        for (j = n-i; j < n; ++j) {
            if (is_prime(mat[i][j])) {
                mat[i][j] = mat[n-1-j][n-1-i];
            }
        }
    }
}

int main(int argc, char *argv[])
{
    int n, **mat, i, j;

    if (argc != 2) {
        return 2;
    }
    n = atoi(argv[1]);

    mat = malloc(n * sizeof(*mat));
    ALLOC_CHECK(mat);

    for (i = 0; i < n; ++i) {
        mat[i] = malloc(n * sizeof(**mat));
        ALLOC_CHECK(mat[i]);
        
        printf("\nUneti elemente %d. vrste:\n", i);
        for (j = 0; j < n; ++j) {
            scanf("%d", mat[i]+j);
        }
    }

    modify(mat, n);

    printf("\nMatrica nakon obrade:\n");
    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            printf("%d\t", mat[i][j]);
        }
        printf("\n\n");
        
        free(mat[i]);
    }

    free(mat);
    return 0;
}
