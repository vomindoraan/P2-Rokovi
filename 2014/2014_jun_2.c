#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DAT_PROD "prodavnica.txt"
#define DAT_POTR "potrepstine.txt"
#define DAT_FAKT "faktura.txt"

#define MAX_NAZ 30

#define PROV_DAT(p) if (!(p)) perror(NULL), exit(1)
#define PROV_MEM(p) if (!(p)) fputs("Neuspesna alokacija", stderr), exit(2)

typedef struct elem {
    char  naziv[MAX_NAZ];
    int   kol;
    float jed_cena;
    struct elem *sled;
} Elem;

Elem *ucitaj_listu(FILE *fp)
{
    Elem *prvi = NULL, *posl;
    char naziv[MAX_NAZ];
    int kol;
    float jed_cena;

    while (fscanf(fp, "%s%d%f", naziv, &kol, &jed_cena) == 3) {
        Elem *novi;
        PROV_MEM(novi = malloc(sizeof *novi));

        strcpy(novi->naziv, naziv);
        novi->kol = kol;
        novi->jed_cena = jed_cena;
        novi->sled = NULL;

        if (!prvi) prvi = novi;
        else       posl->sled = novi;
        posl = novi;
    }

    return prvi;
}

void brisi_listu(Elem *prvi)
{
    while (prvi) {
        Elem *stari = prvi;
        prvi = prvi->sled;
        free(stari);
    }
}

Elem *nadji(Elem *prvi, const char *naziv)
{
    Elem *tek;
    for (tek = prvi; tek; tek = tek->sled)
        if (!strcmp(tek->naziv, naziv)) return tek;
    return NULL;
}

void ispisi_listu(Elem *prvi, FILE *fp_potr, FILE *fp_fakt)
{
    char naziv[MAX_NAZ];
    int kol;
    float ukupno = 0;

    while (fscanf(fp_potr, "%s%d", &naziv, &kol) == 2) {
        Elem *p = nadji(prvi, naziv);
        if (!p || p->kol < kol) continue;

        float cena = kol * p->jed_cena;
        ukupno += cena;

        p->kol -= kol;

        fprintf(fp_fakt, "%s %d %g %.2f\n", naziv, kol, p->jed_cena, cena);
    }

    fprintf(fp_fakt, "%.2f\n", ukupno);
}

int main(void)
{
    FILE *fp_prod, *fp_potr, *fp_fakt;
    PROV_DAT(fp_prod = fopen(DAT_PROD, "r"));
    PROV_DAT(fp_potr = fopen(DAT_POTR, "r"));
    PROV_DAT(fp_fakt = fopen(DAT_FAKT, "w"));
        
    Elem *lista = ucitaj_listu(fp_prod);

    ispisi_listu(lista, fp_potr, fp_fakt);

    brisi_listu(lista);
    fclose(fp_prod);
    fclose(fp_potr);
    fclose(fp_fakt);
}
