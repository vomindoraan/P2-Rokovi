#include <stdio.h>

#define N_MAX 1000

int main(void)
{
    while (1) {
        int n;
        scanf("%u", &n);
        if (n < 3) break;

        unsigned array[N_MAX];
        for (int i = 0; i < n; i++) {
            scanf("%u", &array[i]);
        }

        for (int i = 0; i < n; i++) {
            printf("%u ", array[i]);
        }
        putchar('\n');

        for (int i = 0; i < n; i++) {
            int removed = 0;
            for (int j = i+1, k = j; j < n; j++) {
                if (array[i] != array[j]) {
                    array[k++] = array[j];
                } else {
                    removed++;
                }
            }
            n -= removed;
        }

        for (int i = 0; i < n; i++) {
            printf("%u ", array[i]);
        }
        putchar('\n');

        unsigned max0 = 0, max1 = 0, max2 = 0;
        for (int i = 0; i < n; i++) {
            if (array[i] > max0) {
                max2 = max1;
                max1 = max0;
                max0 = array[i];
            } else if (array[i] > max1) {
                max2 = max1;
                max1 = array[i];
            } else if (array[i] > max2) {
                max2 = array[i];
            }
        }

        if (n >= 1) printf("%u\n", max0);
        if (n >= 2) printf("%u\n", max1);
        if (n >= 3) printf("%u\n", max2);
        for (int i = 0; i < 3-n; i++) puts("x");
    }

    return 0;
}

// Test:
// 11
// 1 10 1 2 2 5 6 7 8 7 7
// 5
// 1 1 1 1 1
// 0
