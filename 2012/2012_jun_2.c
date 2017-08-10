#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_IN  "kalendar.txt"
#define FILE_OUT "preklapanja.txt"
#define BUF_LEN  81

#define FILE_CHECK(f) if (!(f)) printf("Neuspesno otvaranje fajla\n"), exit(1)

typedef struct elem {
    unsigned start, finish;
    char descr[BUF_LEN];
    struct elem *next;
} Elem;

void read_activities(Elem **plist, FILE *fin)
{
    unsigned sh, sm, fh, fm;
    char buf[BUF_LEN];

    while (fscanf(fin, "%u:%u-%u:%u %80[^\n]", &sh, &sm, &fh, &fm, buf) == 5) {
        Elem *p = malloc(sizeof *p), *curr, *prev;
        if (!p) {
            printf("Neuspesna alokacija\n");
            exit(2);
        }

        p->start = sh * 60 + sm;
        p->finish = fh * 60 + fm;
        strcpy(p->descr, buf);

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
            fprintf(fout, "%u:%u-%u:%u %s\n", sh, sm, fh, fm, q->descr);

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
    FILE_CHECK(fin);
    read_activities(&list, fin);
    fclose(fin);

    fout = fopen(FILE_OUT, "w");
    FILE_CHECK(fout);
    remove_overlaps(list, fout);
    fclose(fout);

    free_list(&list);
    return 0;
}
