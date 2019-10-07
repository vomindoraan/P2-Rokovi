#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_IN  "kalendar.txt"
#define FILE_OUT "preklapanja.txt"
#define DESC_LEN 81

#define CHECK_ALLOC(p) if (!(p)) printf("Neuspesna alokacija\n"), exit(1)
#define CHECK_FILE(f)  if (!(f)) printf("Neuspesno otvaranje fajla\n"), exit(2)

typedef struct elem {
    unsigned start, finish;
    char desc[DESC_LEN];
    struct elem *next;
} Elem;

void read_activities(Elem **plist, FILE *fin)
{
    unsigned sh, sm, fh, fm;
    char desc[DESC_LEN];

    while (fscanf(fin, "%u:%u-%u:%u %80[^\n]", &sh, &sm, &fh, &fm, desc) == 5) {
        Elem *p = malloc(sizeof *p), *curr, *prev;
        CHECK_ALLOC(p);
        p->start = sh * 60 + sm;
        p->finish = fh * 60 + fm;
        strcpy(p->desc, desc);

        curr = *plist;
        prev = NULL;
        while (curr && curr->start <= p->start) {
            prev = curr;
            curr = curr->next;
        }
        
        if (prev) {
            prev->next = p;
        } else {
            *plist = p;
        }
        p->next = curr;
    }
}

void remove_overlaps(Elem *list, FILE *fout)
{
    Elem *p = list, *q;
    while (p) {
        q = p->next;
        while (q && q->start < p->finish) {
            unsigned sh, sm, fh, fm;
            p->next = q->next;

            sh = q->start / 60, sm = q->start % 60;
            fh = q->finish / 60, fm = q->finish % 60;
            fprintf(fout, "%u:%u-%u:%u %s\n", sh, sm, fh, fm, q->desc);

            free(q);
            q = p->next;
        }
        p = p->next;
    }
}

void free_list(Elem **plist)
{
    Elem *p;
    while (*plist) {
        p = *plist;
        *plist = (*plist)->next;
        free(p);
    }
    *plist = NULL;
}

int main(void)
{
    FILE *fin, *fout;
    Elem *list = NULL;

    fin = fopen(FILE_IN, "r");
    CHECK_FILE(fin);
    read_activities(&list, fin);
    fclose(fin);

    fout = fopen(FILE_OUT, "w");
    CHECK_FILE(fout);
    remove_overlaps(list, fout);
    fclose(fout);

    free_list(&list);
    return 0;
}
