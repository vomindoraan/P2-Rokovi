#include <stdio.h>

#define UKUPNO_KARATA 52
#define KARATA_U_RUCI 5
#define MAX_IGRACA    10
#define GRANICNA_VRED 10

// Imati dva niza { rb₁, rb₂, ... } { poeni₁, poeni₂, ... } je isto što imati
// 1 niz parova { (rb₁,poeni₁), (rb₂,poeni₂), ... }. U C se to radi sa struct.
typedef struct {
    int rb;
    int poeni;
} Igrac;

int main(void)
{
    int n;
    char gl_znak;
    scanf("%d %c", &n, &gl_znak);  // Unete podatke ne treba proveravati

    // Niz parova koji predstavljaju igrače: (rb,poeni)
    Igrac igraci[MAX_IGRACA];

    // Računa ukupan broj poena svakog igrača
    for (int i = 0; i < n; i++) {
        igraci[i].rb = i + 1;
        igraci[i].poeni = 0;

        for (int j = 0; j < KARATA_U_RUCI; j++) {
            int vred;
            char znak;
            scanf("%d %c", &vred, &znak);

            int poeni = (vred > GRANICNA_VRED) ? GRANICNA_VRED : vred;
            if (znak == gl_znak) poeni *= 2;
            igraci[i].poeni += poeni;
        }
    }

    // Sortira igrače po poenima
    for (int i = 0; i < n-1; i++) {
        for (int j = i; j < n; j++) {
            if (igraci[i].poeni < igraci[j].poeni) {
                Igrac t = igraci[i];  // Direktna dodela celih struktura
                igraci[i] = igraci[j];
                igraci[j] = t;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        printf("%d %d\n", igraci[i].rb, igraci[i].poeni);
    }
}
