#include <stdio.h>

#define N 16  // Opštije: #define N (sizeof(unsigned)*8)

int main(void)
{
    unsigned x;
    scanf("%u", &x);

    for (unsigned i = 0; i < N/2; i++) {
        unsigned b1 = x & (1 << N-1-i);  // U broju izdvojen i-ti bit spreda
        unsigned b2 = x & (1 << i);      // U broju izdvojen i-ti bit otpozadi

        // Ako su oba 1 ili oba 0, nije komplementarna predstava
        if (!b1 == !b2) {  // ! jer poredimo logičke, ne brojne vrednosti
            puts("NE");    // Npr. kada se izdvoji najviši bit, dobije se broj
            return 1;      // 1000000000000000, što ako se poredi sa najnižim
        }                  // bitom 1 po vrednosti nije tačno iako je bit isti
    }

    puts("DA");
    return 0;
}
