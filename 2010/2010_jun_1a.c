#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_CARS  "automobili.txt"
#define FILE_TRIPS "putovanja.txt"
#define REG_LEN    7

#define CHECK_ALLOC(p) if (!(p)) printf("Neuspesna alokacija\n"), exit(1)
#define CHECK_FILE(f)  if (!(f)) printf("Neuspesno otvaranje fajla\n"), exit(2)
// Umesto drugog printf može perror(NULL) što automatski štampa prikladnu grešku

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
        unsigned size, i = 0;

        Elem *p = malloc(sizeof *p);
        CHECK_ALLOC(p);
        
        if (fscanf(file, "%6s ", p->reg) != 1) {
            return list;
        }

        p->km = 0;
        p->next = NULL;

        p->name = malloc(size = 10);
        CHECK_ALLOC(p->name);

        while ((c = fgetc(file)) != '\n') {
            if (i == size) {
                p->name = realloc(p->name, size *= 2);
                CHECK_ALLOC(p->name);
            }
            p->name[i++] = c;
        }

        p->name[i] = '\0';
        p->name = realloc(p->name, i+1);
        // CHECK_ALLOC nije potreban jer se skraćuje

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

    while (fscanf(file, "%10s %6s %u", date, reg, &km) == 3) {
        Elem *p = list;
        while (p && strcmp(reg, p->reg) != 0) {
            p = p->next;
        }
        if (p) {
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
    CHECK_FILE(file);
    list = read_cars(file);
    fclose(file);

    file = fopen(FILE_TRIPS, "r");
    CHECK_FILE(file);
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
    printf("%s %s\n", q->reg, q->name);

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
    printf("%s %s\n", q->reg, q->name);

    free_list(list);
}
