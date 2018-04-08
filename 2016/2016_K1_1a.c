#include <stdio.h>

#define N_MAX 1000

// Imati dva niza { sif₁, sif₂, ... } { br₁, br₂, ... } je isto što imati jedan
// niz parova { (sif₁,br₁), (sif₂,br₂), ... }. U C se to radi pomoću struktura.
typedef struct {
    int sifra;
    int brpoj;
} Slicica;

int main(void)
{
    Slicica niz[N_MAX];
    int n = 0, sifra;

    puts("Uneti sifre slicica (<= 0 za kraj):");
    while (scanf("%d", &sifra), sifra > 0) {
        int i;
        for (i = 0; i < n && niz[i].sifra != sifra; i++);

        if (i == n) {  // Nije nađena sličica, dodaj novu
            niz[i].sifra = sifra;
            niz[i].brpoj = 1;
            n++;
        } else {       // Nađena je sličica, uvećaj br. poj.
            niz[i].brpoj++;
        }
    }

    for (int i = 0; i < n-1; i++) {
        for (int j = i; j < n; j++) {
            if (niz[i].brpoj < niz[j].brpoj) {
                Slicica t = niz[i];  // Direktna dodela celih struktura
                niz[i] = niz[j];
                niz[j] = t;
            }
        }
    }

    puts("Preostale slicice:");
    int i;
    for (i = 0; i < n && niz[i].brpoj > 1; i++) {
        printf("sifra: %d, br. poj: %d\n", niz[i].sifra, niz[i].brpoj);
    }
    n = i;  // Skraćivanje niza na samo duplikate
}
