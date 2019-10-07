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

        unsigned max[] = {0, 0, 0};
        for (int i = 0; i < n; i++) {
            if (array[i] > max[0]) {
                max[2] = max[1];
                max[1] = max[0];
                max[0] = array[i];
            } else if (array[i] > max[1]) {
                max[2] = max[1];
                max[1] = array[i];
            } else if (array[i] > max[2]) {
                max[2] = array[i];
            }
        }

        for (int i = 0; i < 3; i++) {
            if (n > i) {
                printf("%u\n", max[i]);
            } else {
                puts("x");
            }
        }
    }

    return 0;
}

// Test:
// 11
// 1 10 1 2 2 5 6 7 8 7 7
// 5
// 1 1 1 1 1
// 0
