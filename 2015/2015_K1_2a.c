#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LISTICA 100
#define MAX_BROJEVA 50

int main()
{
    srand(time(NULL));

    int m;
    printf("Uneti broj listica: ");
    scanf("%d", &m);
    if (m < 1 || m > MAX_LISTICA) return 1;

    int n;
    printf("Uneti broj brojeva: ");
    scanf("%d", &n);
    if (n < 1 || n > MAX_BROJEVA) return 2;

    // kombinacije[i][broj] == true ako je na i-tom listiću zaokružen broj
    bool kombinacije[MAX_LISTICA][MAX_BROJEVA+1] = { 0 };
    printf("\nUneti kombinacije:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0, broj; j < n; j++) {
            scanf("%d", &broj);
            kombinacije[i][broj] = true;
        }
    }

    bool dobitna[MAX_BROJEVA+1] = { 0 };
    printf("\nDobitna kombinacija:\n");
    for (int i = 0; i < n;) {
        int broj = rand()/(RAND_MAX+1.0) * MAX_BROJEVA + 1;
        printf("Izvucen %d. broj: %d\n", i+1, broj);

        if (!dobitna[broj]) {
            i += dobitna[broj] = true;
        } else {
            printf("Broj postoji, ponavlja se\n");
        }
    }

    int n_pogodaka = 0, n_1_pogodaka = 0;
    for (int i = 0; i < m; i++) {
        int p = 0;
        for (int j = 1; j <= MAX_BROJEVA; j++) {
            p += kombinacije[i][j] && dobitna[j];
        }
        if (p == n)   n_pogodaka++;
        if (p == n-1) n_1_pogodaka++;
    }

    printf("\nBroj listica sa %d pogodaka: %d\n", n, n_pogodaka);
    printf("Broj listica sa %d pogodaka: %d\n", n-1, n_1_pogodaka);
    return 0;
}
