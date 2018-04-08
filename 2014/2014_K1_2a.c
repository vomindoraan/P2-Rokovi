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

        // Sortira ceo niz nerastuće, tako da idu prvo neparni pa parni
        int even = 0;  // Mesto prvog parnog broja
        for (int i = 0; i < n-1; i++) {
            for (int j = i+1; j < n; j++) {
                int ip = !(a[i] % 2), jp = !(a[j] % 2);
                if (ip && !jp || (ip || !jp) && a[i] < a[j]) {
                    SWAP(a[i], a[j]);
                }
            }
            if (a[i] % 2) even = i+1;
        }
        // Obrće parni deo niza da bude uređen neopadajuće
        for (int i = even, j = n-1; i < j; i++, j--) {
            SWAP(a[i], a[j]);
        }

        for (int i = 0; i < n; i++) {
            printf("%d ", a[i]);
        }
        printf("\n\n");
    }
}
