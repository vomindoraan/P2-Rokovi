#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* -------------------------------------------------------------------------- */

// Definicije imena datoteka
#define PHONEBOOK_FILE "imenik.dat"
#define INPUT_FILE     "ulaz.txt"
#define OUTPUT_FILE    "izlaz.txt"

// Najveća dužina imena, telefona i najveći broj unosa u dnevniku
#define NAME_LEN    31
#define NUM_LEN     11
#define MAX_ENTRIES 300

/* -------------------------------------------------------------------------- */

// U jednoj naredbi štampa grešku i izlazi iz programa
// perror je ugrađena f-ja koja sama ištampa ime fajla a potom i poruku greške,
// npr. "izlaz.txt: Access denied" ili "imenik.dat: No such file or directory"
#define IO_ERROR(f) perror(f), exit(1)

// Otvara fajl, vrši proveru, izlazi po potrebi
#define ASSIGN(p, f, m) if (!((p) = fopen(f, m))) IO_ERROR(f)

// Umesto da svaki put kad otvaramo fajl pišemo 5 linija koda:
// p = fopen("ime fajla", "r");
// if (!p) {
//    perror("ime fajla");
//    exit(1);
// }
// možemo u samo jednoj liniji napisati: ASSIGN(p, "ime fajla", "r");

/* -------------------------------------------------------------------------- */

// Struktura za jedan unos imenika, sadrži ime i broj telefona 
typedef struct entry {
    char name[NAME_LEN], num[NUM_LEN];
} Entry;

// Ne treba nam lista jer može imati maksimalno 300 unosa, pa je niz dovoljan
// Ovo je upravo zato da bi se učitavanje moglo lako uraditi sa fread
typedef Entry Phonebook[MAX_ENTRIES];

/* -------------------------------------------------------------------------- */

// Popunjava imenik `pb` iz ulazne datoteke, vraća novu veličinu imenika
int read_phonebook(Phonebook pb)  // Nije potrebna * zato što je to niz
{
    int n;
    FILE *pb_file;

    ASSIGN(pb_file, PHONEBOOK_FILE, "rb");  // ASSIGN na delu

    // Učitava zapise u niz, vraća broj uspešno pročitanih zapisa
    n = fread(pb, sizeof(Entry), MAX_ENTRIES, pb_file);

    fclose(pb_file);
    return n;
}

/* -------------------------------------------------------------------------- */

// Dohvata broj telefona iz imenika `pb` za osobu sa imenom `name`
// Imenik je dužine `n`; f-ja vraća NULL ako osoba ne postoji
char *get_num_for(Phonebook pb, int n, char *name)
{
    int i;
    for (i = 0; i < n; ++i) {
        if (strcmp(pb[i].name, name) == 0) {  // Poređenje obavezno sa strcmp!
            return pb[i].num;
        }
    }
    return NULL;
}

/* -------------------------------------------------------------------------- */

// Glavna obrada: prolazi kroz ulaznu datoteku, vrši zamene, ispisuje u izlaznu
void process_input(Phonebook pb, int n)
{
    FILE *input, *output;
    int c;
    char name[NAME_LEN], *num;  // Pomoćne promenljive za ime i broj

    ASSIGN(input, INPUT_FILE, "r");
    ASSIGN(output, OUTPUT_FILE, "w");

    while ((c = fgetc(input)) != EOF) {
        if (c != '[') {
            fputc(c, output);  // Ako znak nije [, samo ga prepisuje
        } else {
            // Kad se naiđe na [, treba pročitati ono što piše unutar zagrada
            // Ovaj fscanf čita maks. 30 znakova ili do prvog ] i pamti u `name`
            fscanf(input, "%30[^]]]", name);

            // Objašnjenje: % označava početak formata, 30 označava maks. dužinu
            // stringa, npr. "%30s" — pročitaj string od najviše 30 znakova.
            // [] za format označava specijalni tip stringa koji sadrži samo one
            // znakove koji se nalaze između zagrada, npr. "%[abc]" — pročitaj
            // string koji sadrži samo a, b i c.
            // Kada se iza [ umetne ^ to znači da se uslov OBRĆE, npr. "%[^abc]"
            // — pročitaj string koji sadrži sve OSIM a, b i c.
            // Pošto hoćemo da se učitavanje vrši dok se ne dođe do prvog ],
            // to ćemo staviti unutar zagrada. Međutim, pošto ] ima posebno
            // značenje za format, ] zapisujemo kao ]] da bi on znao da je to
            // običan znak a ne kraj formata (slično apostrofima u Paskalu).

            num = get_num_for(pb, n, name);  // Dohvata se broj za pročitano ime
            if (num) {
                fprintf(output, "%s", num);  // Broj postoji, ispiši ga
            } else {
                fprintf(output, "[%s]", name);  // U supr. ispiši ime i zagrade
            }
        }
    }

    fclose(input);
    fclose(output);
}

/* -------------------------------------------------------------------------- */

// Pomoćna funkcija za pravljenje binarne datoteke sa imenikom radi testiranja
void make_phonebook_file(void)
{
    FILE *pb_file;
    Phonebook pb;
    int i, n;

    ASSIGN(pb_file, PHONEBOOK_FILE, "wb");

    printf("Broj zapisa: ");
    scanf("%d", &n);
    if (n < 1 || n > MAX_ENTRIES) {
        return;
    }

    for (i = 0; i < n; ++i) {
        printf("Zapis %d:\n", i);
        scanf("%s %s", pb[i].name, pb[i].num);
    }

    fwrite(pb, sizeof(Entry), i, pb_file);
    fclose(pb_file);
}

/* -------------------------------------------------------------------------- */

int main(void)
{
    Phonebook pb;
    int n;
    
    // make_phonebook_file();
    
    n = read_phonebook(pb);
    process_input(pb, n);

    return 0;
}
