#include <stdio.h>
#include <stdlib.h>

#define MAX 100

unsigned read(unsigned a[]) {
    unsigned n, i;

    scanf("%u", &n);
    if (n > MAX) exit(1);

    for (i = 0; i < n; i++) scanf("%u", a+i);

    return n;
}

void transform(unsigned a[], unsigned b[], unsigned n)
{
    unsigned i, x, y, z, e;

    for (i = 0; i < n; i++) {
        x = a[i];
        y = x - 1;

        e = 0;
        while (y >>= 1) e++;  // e = log2(x-1)

        y = 1U << e;    // Niži stepen
        z = 1U << e+1;  // Viši stepen

        // Uzima bliži; ako su jednako udaljeni, uzima viši zbog <
        b[i] = (abs(x-y) < abs(x-z)) ? y : z;
    }
}

void write(unsigned b[], unsigned n)
{
    unsigned i;
    for (i = 0; i < n; i++) printf("%u ", b[i]);
    putchar('\n');
}

int main(void)
{
    unsigned a[MAX], b[MAX], n;
    n = read(a);
    transform(a, b, n);
    write(b, n);
}
