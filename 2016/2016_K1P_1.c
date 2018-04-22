#include <stdio.h>

#define N_MAX 100
#define MASK  3U

unsigned broj_parova(unsigned x)
{
    unsigned br = 0;
    while (x != 0) {
        if ((x & MASK) == MASK) br++;
        x >>= 1;
    }
    return br;
}

int main(void)
{
    unsigned n;
    printf("Uneti broj elemenata niza: ");
    scanf("%u", &n);
    if (n < 1 || n > N_MAX) return 1;

    // Učitava elemente (niz a) i računa broj parova za svaki (niz b)
    unsigned a[N_MAX], b[N_MAX];
    printf("Uneti elemente niza:\n");
    for (unsigned i = 0; i < n; i++) {
        scanf("%u", &a[i]);
        b[i] = broj_parova(a[i]);
    }

    // Računa prosečan broj parova
    double prosek = 0;
    for (unsigned i = 0; i < n; i++) {
        prosek += b[i];
    }
    prosek /= n;

    // Iz nizova izbacuje članove čiji je broj parova veći od prosečnog
    unsigned j = 0;
    for (unsigned i = 0; i < n; i++) {
        a[j] = a[i];
        b[j] = b[i];
        if (b[i] <= prosek) j++;  // Treba zadržati a[i] i b[i]
    }
    n = j;

    // Optimizovani selection sort (ne radi nepotrebne zamene) i ispis
    printf("\nRezultujuci niz:\n");
    for (unsigned i = 0; i < n; i++) {
        unsigned imax = i, t;
        for (unsigned j = i+1; j < n; j++) {
            if (a[imax] < a[j]) imax = j;
        }
	t = a[i], a[i] = a[imax], a[imax] = t;

        printf("%u ", a[i]);
    }
    return 0;
}
