#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N_MAX 100
#define LOW   100
#define HIGH  200

#define SWAP(x, y) { int t = (x); (x) = (y); (y) = t; }
// #define SWAP(x, y) ((x) ^= (y) ^= (x) ^= (y))

int main(void)
{
    int a[N_MAX], n;
    srand(time(NULL));

    while (scanf("%d", &n), n > 0 && n <= N_MAX) {
        for (int i = 0; i < n; i++) {
            a[i] = rand()/(RAND_MAX+1.0) * (HIGH-LOW+1) + LOW;
        }

        // Sortira neparni deo niza, usput pamti gde počinje parni
        int even = 0;  // Mesto prvog parnog broja
        for (int i = 0; i < n-1; i++) {
            for (int j = i+1; j < n; j++) {
                if (a[i] % 2 == 0 || a[j] % 2 == 1 && a[i] < a[j]) {
                    SWAP(a[i], a[j]);
                }
            }
            if (a[i] % 2 == 1) even = i+1;
        }
        // Sortira parni deo niza
        for (int i = even; i < n-1; i++) {
            for (int j = i+1; j < n; j++) {
                if (a[i] > a[j]) {
                    SWAP(a[i], a[j]);
                }
            }
        }

        for (int i = 0; i < n; i++) {
            printf("%d ", a[i]);
        }
        printf("\n\n");
    }
}
