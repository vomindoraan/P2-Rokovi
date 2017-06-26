#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_USERS "korisnici.txt"
#define FILE_LOG   "log.txt"
#define NAME_LEN   21
#define EMAIL_LEN  41

#define MAX(a, b)      (((a) > (b)) ? (a) : (b))
#define ALLOC_CHECK(p) if (!(p)) fputs("Neuspesna alokacija", stderr), exit(1)
#define FILE_CHECK(f)  if (!(f)) perror(NULL), exit(2) // perror stampa poruku

typedef struct elem {
    char name[NAME_LEN];
    char email[EMAIL_LEN];
    int  logon;
    int  total;
    struct elem *next;
} Elem;

Elem *read_list(FILE *fp)
{
    Elem *head = NULL, *tail;
    char name[NAME_LEN], email[EMAIL_LEN];

    // fscanf vraca broj uspesno procitanih vrednosti
    while (fscanf(fp, "%s %s", name, email) == 2) {
        Elem *p = malloc(sizeof *p);
        ALLOC_CHECK(p);

        strcpy(p->name, name);
        strcpy(p->email, email);
        p->logon = p->total = 0;
        p->next = NULL;

        if (head) tail->next = p;
        else      head = p;
        tail = p;
    }

    return head;
}

void update_list(Elem *list, FILE *fp)
{
    char email[EMAIL_LEN], action;
    int time;

    while (fscanf(fp, "%s %c %d", email, &action, &time) == 3) {
        Elem *p = list;
        while (strcmp(p->email, email)) p = p->next;

        if (!p) continue; // Korisnik ne postoji u listi

        /**/ if (action == 'p') // Korisnik nadjen
            p->logon = time;
        else if (action == 'o')
            p->total += time - p->logon;
    }
}

void free_list(Elem **plist)
{
    while (*plist) {
        Elem *p = *plist;
        *plist = (*plist)->next;
        free(p);
    }
}

int main(void)
{
    FILE *fp_users, *fp_log;
    FILE_CHECK(fp_users = fopen(FILE_USERS, "r"));
    FILE_CHECK(fp_log   = fopen(FILE_LOG,   "r"));

    Elem *list = read_list(fp_users);
    update_list(list, fp_log);

    int max_time = 0;
    for (Elem *p = list; p; p = p->next)
        max_time = MAX(max_time, p->total); // Nalazi najvece vreme

    for (Elem *p = list; p; p = p->next)
        if (p->total == max_time) {
            p->name[0] = toupper(p->name[0]);
            puts(p->name); // Ispisuje sve sa tim vremenom (moze i samo 1)
        }

    free_list(&list);
    fclose(fp_users);
    fclose(fp_log);
}
