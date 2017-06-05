#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_CARS  "automobili.txt"
#define FILE_TRIPS "putovanja.txt"
#define REG_LEN    7
#define NAME_LEN   101

#define ALLOC_CHECK(p) if (!(p)) printf("Neuspesna alokacija\n"), exit(1)
#define FILE_CHECK(f)  if (!(f)) printf("Neuspesno otvaranje fajla\n"), exit(2)
// Umesto 2. printf() moze perror(NULL) koje automatski stampa prikladnu gresku

typedef struct elem {
    char reg[REG_LEN];
    char *name;
    unsigned km;
    struct elem *next;
} Elem;

Elem *read_cars(FILE *file)
{
    Elem *list = NULL, *prev = NULL;

    while (1) {
        char c;
        unsigned size, i;

        Elem *p = malloc(sizeof *p);
        ALLOC_CHECK(p);
        
        if (fscanf(file, "%6s", p->reg) != 1) {
            break;
        }

        p->km = 0;
        p->next = NULL;

        i = 0;
        p->name = malloc(size = 10);
        ALLOC_CHECK(p->name);

        while ((c = fgetc(file)) != '\n') {
            if (i == size) {
                p->name = realloc(p->name, size *= 2);
                ALLOC_CHECK(p->name);
            }
            p->name[i++] = c;
        }

        p->name[i] = '\0';
        p->name = realloc(p->name, i+1);
        // ALLOC_CHECK nije potreban jer se skracuje

        if (!list) {
            list = p;
        } else {
            prev->next = p;
        }
        prev = p;
    }
}

void read_trips(FILE *file, Elem *list)
{
    char date[11], reg[REG_LEN];
    unsigned km;

    while (fscanf(file, "%s %6s %u", date, reg, &km) == 3) {
        Elem *p = list;
        while (p && strcmp(reg, p->reg) == 0) {
            p = p->next;
        }
        if (strcmp(reg, p->reg) == 0) {
            p->km += km;
        }
    }
}

void free_list(Elem *list)
{
    while (list) {
        Elem *p = list;
        list = p->next;
        free(p);
    }
}

int main(void)
{
    FILE *file;
    Elem *list, *p, *q;
    unsigned km;

    file = fopen(FILE_CARS, "r");
    FILE_CHECK(file);
    list = read_cars(file);
    fclose(file);

    file = fopen(FILE_TRIPS, "r");
    FILE_CHECK(file);
    read_trips(file, list);
    fclose(file);

    q = list;
    km = q->km;
    p = list->next;
    while (p) {
        if (p->km < km) {
            km = p->km;
            q = p;
        }
        p = p->next;
    }
    printf("%s %u\n", q->reg, q->km);

    q = list;
    km = q->km;
    p = list->next;
    while (p) {
        if (p->km > km) {
            km = p->km;
            q = p;
        }
        p = p->next;
    }
    printf("%s %u\n", q->reg, q->km);

    free_list(list);
    return 0;
}