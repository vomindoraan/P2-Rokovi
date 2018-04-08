#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LISTICA 100
#define MAX_BROJEVA 50

// Generiše pseudoslučajan ceo broj u opsegu [low, high]
int generisi(int low, int high) {
    return rand()/(RAND_MAX+1.0) * (high-low+1) + low;
}

// Proverava da li niz dužine n sadrži zadatu vrednost
int sadrzi(int niz[], int n, int vr)
{
    int i;
    for (i = 0; i < n && niz[i] != vr; i++);
    return i < n;
}

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

    int kombinacije[MAX_LISTICA][MAX_BROJEVA];
    printf("\nUneti kombinacije:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &kombinacije[i][j]);
        }
    }

    int dobitna[MAX_BROJEVA];
    printf("\nDobitna kombinacija:\n");
    for (int i = 0; i < n;) {
        int broj = generisi(1, MAX_BROJEVA);
        printf("Izvucen %d. broj: %d\n", i+1, broj);

        if (!sadrzi(dobitna, i, broj)) {
            dobitna[i++] = broj;  // Broj ne postoji, dodaj ga
        } else {
            printf("Broj postoji, ponavlja se\n");
        }
    }

    int n_pogodaka = 0, n_1_pogodaka = 0;
    for (int i = 0; i < m; i++) {
        int p = 0;
        for (int j = 0; j < n; j++) {
            p += sadrzi(dobitna, n, kombinacije[i][j]);
        }
        if (p == n)   n_pogodaka++;
        if (p == n-1) n_1_pogodaka++;
    }

    printf("\nBroj listica sa %d pogodaka: %d\n", n, n_pogodaka);
    printf("Broj listica sa %d pogodaka: %d\n", n-1, n_1_pogodaka);
    return 0;
}
