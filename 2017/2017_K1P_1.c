#include <stdio.h>
#include <stdlib.h>  // RAND_MAX, rand, srand
#include <time.h>    // time

#define N_MAX 100

// Generiše pseudoslučajan ceo broj u opsegu [low, high]
int random(int low, int high)
{
    return rand()/(double)RAND_MAX * (high-low) + low;
}

int main(void)
{
    srand(time(NULL));

    int n;
    printf("Uneti duzinu niza: ");
    scanf("%d", &n);
    if (n % 2 || n < 1 || n > N_MAX) return 1;

    unsigned a[N_MAX];
    printf("Uneti niz:\n");
    for (int i = 0; i < n; i++) {
        scanf("%u", &a[i]);
    }

    int x = random(0, 31), y;
    do {
        y = random(0, 31);
    } while (y < x);

    unsigned mask = 0;
    for (int i = x; i <= y; i++) mask |= 1<<i;
    // Može i: mask = (1 << y-x+1) - 1;

    // Zamenjuje grupu bita od x. do y. između brojeva a[k] i a[k+1]
    for (int k = 0; k < n; k += 2) {
        unsigned t1 = (a[k]   & ~mask) | (a[k+1] & mask);
        unsigned t2 = (a[k+1] & ~mask) | (a[k]   & mask);
        a[k] = t1, a[k+1] = t2;
    }

    printf("\nX = %d, Y = %d\n", x, y);
    for (int i = 0; i < n; i++) {
        printf("%u ", a[i]);
    }
}
