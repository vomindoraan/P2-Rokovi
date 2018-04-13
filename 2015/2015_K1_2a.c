#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LISTICA 100
#define MAX_BROJEVA 50

int main(void)
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

    // kombinacije[i][broj] je 1 ako je na i-tom listiću zaokružen broj
    int kombinacije[MAX_LISTICA][MAX_BROJEVA+1] = { 0 };  // Na početku sve 0
    printf("Uneti kombinacije:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0, broj; j < n; j++) {
            scanf("%d", &broj);
            kombinacije[i][broj] = 1;
        }
    }

    // dobitna[broj] daje da li je broj izvučen ili ne
    int dobitna[MAX_BROJEVA+1] = { 0 };  // Na početku sve 0
    for (int j = 0; j < n; j++) {
        int broj = rand()/(RAND_MAX+1.0) * MAX_BROJEVA + 1;
        if (!dobitna[broj]) {
            dobitna[broj] = 1;  // Kad izvuče novi broj, postavi na 1
            printf("Izvucen broj %d\n", broj);
        } else j--;             // U suprotnom ponovi izvlačenje
    }

    int n_pogodaka = 0, n_1_pogodaka = 0;
    for (int i = 0; i < m; i++) {  // Za svaki listić
        int p = 0;
        for (int j = 1; j <= MAX_BROJEVA; j++) {  // Za svaki moguć broj
            // Ako je broj u listiću i u dobitnoj, uvećaj broj pogodaka
            if (kombinacije[i][j] && dobitna[j]) p++;
        }
        if (p == n)   n_pogodaka++;
        if (p == n-1) n_1_pogodaka++;
    }

    printf("N pogodaka:   %d\n"
           "N-1 pogodaka: %d\n", n_pogodaka, n_1_pogodaka);
    return 0;
}
