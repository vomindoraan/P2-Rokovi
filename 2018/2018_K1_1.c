#include <stdio.h>

#define UKUPNO_KARATA 52
#define KARATA_U_RUCI 5
#define MAX_IGRACA    10
#define GRANICNA_VRED 10

#define ZAMENI(x, y) { int t = (x); (x) = (y); (y) = t; }
// #define ZAMENI(x, y) ((x) ^= (y) ^= (x) ^= (y))

int main(void)
{
    int n;
    char gl_znak;
    scanf("%d %c", &n, &gl_znak);  // Unete podatke ne treba proveravati

    // Niz r.b. treba kako se pri sortiranju po poenima ne bi pomešalo ko je ko
    int rb[MAX_IGRACA], poeni[MAX_IGRACA];

    // Računa ukupan broj poena svakog igrača
    for (int i = 0; i < n; i++) {
        rb[i] = i + 1;
        poeni[i] = 0;

        for (int j = 0; j < KARATA_U_RUCI; j++) {
            int vred;
            char znak;
            scanf("%d %c", &vred, &znak);

            if (vred > GRANICNA_VRED) vred = GRANICNA_VRED;
            if (znak == gl_znak) vred *= 2;
            poeni[i] += vred;
        }
    }

    // Sortira igrače po poenima
    for (int i = 0; i < n-1; i++) {
        for (int j = i; j < n; j++) {
            if (poeni[i] > poeni[j]) {
                ZAMENI(poeni[i], poeni[j]);
                ZAMENI(rb[i], rb[j]);  // Menja i r.b. da bi se znalo ko je ko
            }
        }
    }

    for (int i = 0; i < n; i++) {
        printf("%d %d\n", rb[i], poeni[i]);
    }
}
