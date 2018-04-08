#include <stdio.h>

#define N_MAX 1000

#define ZAMENI(x, y) { int t = (x); (x) = (y); (y) = t; }
// #define ZAMENI(x, y) ((x) ^= (y) ^= (x) ^= (y))

int main(void)
{
    int sifre[N_MAX];
    int brpoj[N_MAX] = { 0 };  // Sve nule
    int n = 0, sifra;

    // Učitava šifre sličica i računa broj pojavljivanja
    while (scanf("%d", &sifra), sifra > 0) {
        int i;  // Položaj šifre u nizu (n ako šifra ne postoji)
        for (i = 0; i < n && sifre[i] != sifra; i++);
        sifre[i] = sifra;
        brpoj[i]++;
        if (i == n) n++;
    }

    // Uređuje sličice nerastuće po broju pojavljivanja
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (brpoj[i] < brpoj[j]) {
                ZAMENI(sifre[i], sifre[j]);
                ZAMENI(brpoj[i], brpoj[j]);
            }
        }
    }

    // Izbacuje sa kraja niza sve koje se pojavljuju jednom
    while (brpoj[--n] == 1);
    n++;

    // Ispisuje preostale
    for (int i = 0; i < n; i++) {
        printf("%d %d\n", sifre[i], brpoj[i]);
    }
}
