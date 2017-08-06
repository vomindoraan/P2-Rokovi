#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define ALLOC_CHECK(p) if (!(p)) puts("Neuspesna alokacija"), exit(1)

bool is_palindrome(unsigned x)
{
    unsigned i, j, n = 8 * sizeof x;  // Broj bita unsigned x

    for (i = 1 << n-1, j = 1; i > j; i >>= 1, j <<= 1)
        if (!(x & i) != !(x & j))  // Proverava da li su biti logički različiti
            return false;

    return true;
}

int main(void)
{
    unsigned size = 10, n = 0, i;
    unsigned *a = malloc(size * sizeof(*a));
    ALLOC_CHECK(a);

    puts("Uneti niz celih brojeva:");
    while (scanf("%u", &a[n++]))
        if (n == size) {
            size *= 2;
            a = realloc(a, size * sizeof(*a));
            ALLOC_CHECK(a);
        }

    // Može i da se skrati na pravu dužinu sa a = realloc(a, n * sizeof(*a));

    puts("Bitski palindromi su:");
    for (i = 0; i < n; i++)
        if (is_palindrome(a[i]))
            printf("%u ", a[i]);

    free(a);
}
