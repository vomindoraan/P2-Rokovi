#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N_MAX 100
#define LOW   100
#define HIGH  200

// F-ja poređenja: ako x dolazi pre y, vraća -1; ako posle, +1; ako su isti, 0
int cmp(int x, int y)
{
    int xp = !(x % 2), yp = !(y % 2);
    // Ako je različita parnost: levi P, desni NP → -1; levi NP, desni P → +1
    if (xp != yp) return xp ? -1 : +1;
    // U nastavku je ista parnost: oba P ili oba NP
    if (x < y)    return xp ? +1 : -1;  // Ako x < y: oba P → +1; oba NP → -1
    if (x > y)    return xp ? -1 : +1;  // Ako x > y: oba P → -1; oba NP → +1
    return 0;  // Isti su
}

int main(void)
{
    int a[N_MAX], n;
    srand(time(NULL));

    while (scanf("%d", &n), n > 0 && n <= N_MAX) {
        for (int i = 0; i < n; i++) {
            a[i] = rand()/(RAND_MAX+1.0) * (HIGH-LOW+1) + LOW;
        }

        for (int i = 0, t; i < n-1; i++) {
            for (int j = i+1; j < n; j++) {
                if (cmp(a[i], a[j]) < 0) {
                    t = a[i], a[i] = a[j], a[j] = t;
                    // Može i: a[i] ^= a[j] ^= a[i] ^= a[j];
                }
            }
        }

        for (int i = 0; i < n; i++) {
            printf("%d ", a[i]);
        }
        printf("\n\n");
    }
}
