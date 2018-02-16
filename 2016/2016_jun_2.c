#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_USERS "korisnici.txt"
#define FILE_LOG   "log.txt"
#define NAME_LEN   21
#define EMAIL_LEN  51

#define CHECK_ALLOC(p) if (!(p)) printf("Neuspesna alokacija\n"), exit(1)
#define CHECK_FILE(f)  if (!(f)) printf("Neuspesno otvaranje fajla\n"), exit(2)

typedef struct elem {
    char name[NAME_LEN];
    char email[EMAIL_LEN];
    unsigned signin_time, total_time;
    struct elem *next;
} Elem;

Elem *read_users(Elem *list, FILE *fin)
{
    Elem *p, *tail = NULL;
    char name[NAME_LEN], email[EMAIL_LEN];

    while (fscanf(fin, "%20s %50[^\n]", name, email) == 2) {
        CHECK_ALLOC(p = malloc(sizeof *p));
        strcpy(p->name, name);
        strcpy(p->email, email);
        p->signin_time = p->total_time = 0;
        p->next = NULL;

        if (list) {
            tail->next = p;
        } else {
            list = p;
        }
        tail = p;
    }

    return list;
}

void update_list(Elem *list, FILE *fin)
{
    char email[EMAIL_LEN], a;
    unsigned time;
    Elem *p;

    while (fscanf(fin, "%50s %c %u", email, &a, &time) == 3) {
        p = list;
        while (p && strcmp(email, p->email)) {
            p = p->next;
        }
        if (!p) {
            printf("Korisnik %s ne postoji!\n", email);
            continue;
        }

        if (a == 'p') {
            p->signin_time = time;
        } else if (a == 'o' && p->signin_time > 0) {
            p->total_time += time - p->signin_time;
        } else {
            printf("Neispravan format!\n");
            continue;
        }
    }
}

Elem *free_list(Elem *list)
{
    Elem *p;
    while (list) {
        p = list;
        list = list->next;
        free(p);
    }
    return NULL;
}

int main(void)
{
    Elem *list = NULL, *p, *pmax;
    FILE *fu, *fl;

    CHECK_FILE(fu = fopen(FILE_USERS, "r"));
    list = read_users(list, fu);
    fclose(fu);

    CHECK_FILE(fl = fopen(FILE_LOG, "r"));
    update_list(list, fl);
    fclose(fl);

    p = pmax = list;
    while (p) {
        if (p->total_time > pmax->total_time) {
            pmax = p;
        }
        p = p->next;
    }
    printf("%s", pmax->name);

    free_list(list);
    return 0;
}
