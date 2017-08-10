#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LEN 21

#define FILE_IN  "radovi.txt"
#define FILE_OUT "izlaz.txt"

#define POINTS(n) (2.0 / n)

// Proverava fajl i po potrebi izlazi iz programa
#define FILE_CHECK(f) if (!(f)) printf("Neuspesno otvaranje fajla\n"), exit(1)

const char *titles[] = {
    "docent", "vanredni profesor", "redovni profesor"
};

typedef char name_t[NAME_LEN];  // Olakšica da ne bih svuda pisao niz i dužinu

typedef struct elem {
    name_t first;
    name_t last;
    double pts;
    struct elem *next;
} Elem;

// Nalazi autora sa datim imenom i prezimenom i vraća pok. na taj element,
// odnosno NULL ako autor ne postoji ili je lista prazna
Elem *list_find(Elem *list, name_t first, name_t last)
{
    Elem *p = list;
    while (p) {
        if (!strcmp(p->first, first) && !strcmp(p->last, last)) {
            return p;  // Stringovi jednaki
        }
        p = p->next;
    }
    return NULL;
}

// Briše listu
void list_delete(Elem *list)
{
    while (list) {
        Elem *p = list;
        list = list->next;
        free(p);
    }
}

// Učitava autore iz datoteke u listu; vraća pok. na početak liste, odnosno NULL
// ako je datoteka prazna
Elem *read_authors(FILE *fin)
{
    Elem *list = NULL, *tail = NULL;
    int n, i, c;

    // fscanf vraća broj uspešno pročitanih podataka, u ovom slučaju 1
    // Ako ne uspe može vratiti 0, ili EOF (-1) ako dođe do kraja fajla
    while (fscanf(fin, "%d", &n) == 1) {
        for (i = 0; i < n; ++i) {
            name_t first, last;
            Elem *author, *p;

            fscanf(fin, "%20s %20s", first, last);
            author = list_find(list, first, last);

            if (author) {
                author->pts += POINTS(n);  // Ažuriranje poena
                continue;
            }

            p = malloc(sizeof *p);  // Novi autor
            if (!p) {
                printf("Neuspesna alokacija\n");
                exit(2);
            }

            strcpy(p->first, first);
            strcpy(p->last, last);  // Obavezno strcpy, ne može obična dodela
            p->pts = POINTS(n);
            p->next = NULL;

            if (!list) {
                list = p;
            } else {
                tail->next = p;
            }
            tail = p;
        }

        while ((c = fgetc(fin)) != '\n' && c != EOF);  // Čita do kraja reda
    }

    return list;
}

// Ispisuje autore i njihova zvanja u datoteku
void write_authors(FILE *fout, Elem *list)
{
    while (list) {
        const char *title = NULL;  // Pok. na konst. podatak; pok. nije konst.
        int k = sizeof titles / sizeof *titles;  // Dužina niza sa zvanjima

        while (k--) {  // Poredi redom poene sa 3,2,1 dok ne nađe zvanje
            if (list->pts >= k) {
                title = titles[k-1];
                break;
            }
        }

        if (title) {  // Ako je zvanje NULL, ne treba ispisivati
            fprintf(fout, "%s %s %s\n", list->first, list->last, title);
        }

        list = list->next;
    }
}

// Glavni program
int main(void)
{
    FILE *fin, *fout;
    Elem *list;

    FILE_CHECK(fin = fopen(FILE_IN, "r"));
    list = read_authors(fin);
    fclose(fin);

    FILE_CHECK(fout = fopen(FILE_OUT, "w"));
    write_authors(fout, list);
    fclose(fout);

    list_delete(list);
    return 0;
}
