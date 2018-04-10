#include <stdio.h>

int main(void)
{
    unsigned a, b, i = 15;  // Opštije: i = sizeof(b)*8-1;
    scanf("%X%X", &a, &b);

    // Pomera masku ulevo dok 1 ne dođe na najviši bit
    while (!(b & 1<<i)) b <<= 1;

    // Pomera masku udesno dok 1 ne dođe na najniži bit, usput proverava
    for (;; b >>= 1, i--) {
        if ((a & b) == b) printf("%u ", i);
        if (b & 1) break;
    }
}
