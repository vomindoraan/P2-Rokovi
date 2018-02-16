#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REG_LEN  6
#define NAME_LEN 100

#define CHECK_ALLOC(p) if (!(p)) fputs("Neuspesna alokacija", stderr), exit(1)
#define CHECK_FILE(f)  if (!(f)) perror(NULL), exit(2)

typedef struct elem {
    char reg[REG_LEN+1];
    char name[NAME_LEN+1];
    int km;
    struct elem *next;
} Elem;

Elem *read_cars(FILE *file)
{
    Elem *head = NULL, *tail;

    while (1) {
        Elem *new = malloc(sizeof(Elem));
        CHECK_ALLOC(new);

        if (fscanf(file, "%s %[^\n]", new->reg, new->name) != 2) {
            free(new);  // Kada se dođe do kraja, oslobađa neiskorišćeni čvor
            return head;
        }
        // Da bi se sprečilo prekoračenje duž. stringa, format je mogao glasiti
        // "%6s %100[^\n]" (ovo [^\n] znači "čitaj string do kraja reda"). Ali
        // pošto 6 i 100 već postoje gore u konstantama, uz odgovarajuće makroe
        // #define S_(x) #x
        // #define S(x)  S_(x)
        // koji pretvaraju simboličku konstantu u string, format je mogao biti:
        // "%" S(REG_LEN) "s %" S(NAME_LEN) "[^\n]"
        // što je isto kao "%6s %100[^\n]".

        new->km = 0;
        new->next = NULL;

        if (head) tail->next = new;
        else      head = new;
        tail = new;
    }
}

void read_trips(Elem *list, FILE *file)
{
    char date[11];
    char reg[REG_LEN+1];
    int km;

    while (fscanf(file, "%10s %6s %d", date, reg, &km) == 3) {
        Elem *p;
        for (p = list; p; p = p->next)
            if (strcmp(p->reg, reg) == 0)
                break;

        if (p) p->km += km;
    }
}

void free_list(Elem *list)
{
    while (list) {
        Elem *p = list;
        list = list->next;
        free(p);
    }
}

int main(void)
{
    FILE *file;
    CHECK_FILE(file = fopen("automobili.txt", "r"));
    Elem *list = read_cars(file);
    fclose(file);

    if (!list) {
        puts("Lista je prazna");
        return 0;
    }

    CHECK_FILE(file = fopen("putovanja.txt", "r"));
    read_trips(list, file);
    fclose(file);

    Elem *p_min = list, *p_max = list;

    for (Elem *p = list; p; p = p->next) {
        if (p->km < p_min->km) p_min = p;
        if (p->km > p_max->km) p_max = p;
    }
    
    printf("Automobil sa min km:\n%s %s\n\n", p_min->reg, p_min->name);
    printf("Automobil sa max km:\n%s %s\n",   p_max->reg, p_max->name);

    free_list(list);
    return 0;
}
