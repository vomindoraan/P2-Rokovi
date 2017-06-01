#include <stdio.h>

#define MAX 100

int transform(int *a, int n, int *b)
{
    int m = 0, i, j, k, br_el;

    for (i = 0; i < n; ++i) {
        for (j = 0; j < m; j += 2) {
            if (a[i] == b[j]) {
                break;
            }
        }

        if (j == m) {
            br_el = 1;
            for (k = i+1; k < n; ++k) {
                if (a[i] == a[k]) {
                    br_el++;
                }
            }
            b[m++] = a[i];
            b[m++] = br_el;
        }
    }

    return m;
}

int main(void)
{
    int a[MAX], n, b[2*MAX], m, i;

    while (1) {
        printf("\nn? ");
        scanf("%d", &n);

        if (n < 1 || n >= MAX) {
            break;
        }

        printf("niz?\n");
        for (i = 0; i < n; ++i) {
            scanf("%d", &a[i]);
        }

        m = transform(a, n, b);

        printf("b:\n");
        for (i = 0; i < m; ++i) {
            printf("%d ", b[i]);
        }
    }

    return 0;
}
