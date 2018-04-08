// Ideja: kao što je 23.125 = 2·10¹ + 3·10⁰ + 1·10⁻¹ + 2·10⁻² + 5·10⁻³, tako
// je i 10111.001 = 1·2⁴ + 0·2³ + 1·2² + 1·2¹ + 1·2⁰ + 0·2⁻¹ + 0·2⁻² + 1·2⁻³

#include <stdbool.h>
#include <stdio.h>

#define N_MAX 50

int main(void)
{
    char cifre[N_MAX], c;
    int n = 0;
    bool bila_tacka = false;

    printf("Uneti cifre:\n");
    // Učitava znakove ili do kraja reda ili dok ne popuni ceo niz
    while ((c = getchar()) != '\n' && n < N_MAX) {
        // Znak je ispravan ako je '0', '1', ili je prva '.' u redu
        if (c == '0' || c == '1' || (c == '.' && !bila_tacka)) {
            cifre[n++] = c;  // Dodaje znak na kraj niza
            if (c == '.') bila_tacka = true;
        } else {
            printf("Neispravan znak %c, ponoviti unos\n", c);
        }
    }

    int t;  // Položaj tačke u nizu
    for (t = 0; t < n && cifre[t] != '.'; t++);
    // Drugi način: cifre[n] = '\0'; int t = strcspn(cifre, ".");

    double dec = 0;
    // Pretvara ceo deo (do tačke) u decimalni sistem
    for (int i = 0; i < t; i++) {
        int cifra = cifre[i] - '0';
        int stepen = 1 << t-1-i;
        dec += cifra * stepen;  // Pre tačke množenje stepenima dvojke
    }
    // Pretvara realan deo (posle tačke) u decimalni sistem
    for (int i = 1; i < n-t; i++) {
        double cifra = cifre[t+i] - '0';
        int stepen = 1 << i;
        dec += cifra / stepen;  // Posle tačke deljenje stepenima dvojke
    }
    printf("Rezultat: %g\n", dec);
}
