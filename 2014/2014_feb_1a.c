#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* -------------------------------------------------------------------------- */

// Definicije imena datoteka
#define PHONEBOOK_FILE "imenik.dat"
#define INPUT_FILE     "ulaz.txt"
#define OUTPUT_FILE    "izlaz.txt"

// Najveca duzina imena, telefona i najveci br. unosa u dnevniku
#define NAME_LEN    31
#define NUM_LEN     11
#define MAX_ENTRIES 300

/* -------------------------------------------------------------------------- */

// U jednoj naredbi stampa gresku i izlazi iz programa
// perror je ugradjena f-ja koja sama istampa ime fajla a potom i poruku greske
// npr. "izlaz.txt: Access denied" ili "imenik.dat: No such file or directory"
#define IO_ERROR(f) perror(f), exit(1)

// Otvara fajl, vrsi proveru, izlazi po potrebi
#define ASSIGN(p, f, m) if (!((p) = fopen(f, m))) IO_ERROR(f)

// Umesto da svaki put kad otvaramo fajl pisemo 5 linija koda:
// p = fopen("ime fajla", "r");
// if (!p) {
//    perror("ime fajla");
//    exit(1);
// }
// mozemo samo u jednoj liniji da napisemo: ASSIGN(p, "ime fajla", "r");

/* -------------------------------------------------------------------------- */

// Struktura za jedan unos imenika, sadrzi ime i broj telefona 
typedef struct entry {
    char name[NAME_LEN], num[NUM_LEN];
} Entry;

// Ne treba nam lista jer moze imati maksimalno 300 unosa, pa je niz dovoljan
// Ovo je upravo zato da bi se ucitavanje moglo lako uraditi sa fread
typedef Entry Phonebook[MAX_ENTRIES];

/* -------------------------------------------------------------------------- */

// Popunjava imenik 'pb' iz ulazne datoteke, vraca novu velicinu imenika
int read_phonebook(Phonebook pb) // Nije potrebna * zato sto je to niz
{
    int n;
    FILE *pb_file;

    ASSIGN(pb_file, PHONEBOOK_FILE, "rb"); // ASSIGN na delu

    // Ucitava zapise u niz, vraca broj uspesno procitanih zapisa
    n = fread(pb, sizeof(Entry), MAX_ENTRIES, pb_file);

    fclose(pb_file);
    return n;
}

/* -------------------------------------------------------------------------- */

// Dohvata broj telefona iz imenika 'pb' za osobu sa imenom 'name'
// Imenik je duzine 'n'; f-ja vraca NULL ako osoba ne postoji
char *get_num_for(Phonebook pb, int n, char *name)
{
    int i;
    for (i = 0; i < n; ++i) {
        if (strcmp(pb[i].name, name) == 0) { // Poredjenje obavezno sa strcmp!
            return pb[i].num;
        }
    }
    return NULL;
}

/* -------------------------------------------------------------------------- */

// Glavna obrada: prolazi kroz ulaznu datoteku, vrsi zamene, ispisuje u izlaznu
void process_input(Phonebook pb, int n)
{
    FILE *input, *output;
    int c;
    char name[NAME_LEN], *num; // Privremene promenljive za ime i broj

    ASSIGN(input, INPUT_FILE, "r");
    ASSIGN(output, OUTPUT_FILE, "w");

    while ((c = fgetc(input)) != EOF) {
        if (c != '[') {
            fputc(c, output); // Ako znak nije [, samo ga prepisuje
        } else {
            // Kad se naidje na [, treba procitati ono sto pise unutar zagrada
            // Ovaj fscanf cita maks. 30 znakova ili do prvog ] i pamti u 'name'
            fscanf(input, "%30[^]]]", name);

            // Objasnjenje: % oznacava pocetak formata, 30 oznacava maks. duzinu
            // stringa, npr. "%30s" - procitaj string od najvise 30 znakova
            // [] za format oznacava specijalni tip stringa koji sadrzi samo one
            // znakove koji se nalaze izmedju zagrada, npr. "%[abc]" - procitaj
            // string koji sadrzi samo a, b i c
            // Kada se iza [ umetne ^ to znaci da se uslov OBRCE, npr. "%[^abc]"
            // - procitaj string koji sadrzi sve OSIM a, b i c
            // Posto hocemo da se ucitavanje vrsi dok se ne dodje do prvog ],
            // to cemo staviti unutar zagrada, medjutim posto ] ima specijalno
            // znacenje za format, ] zapisujemo kao ]] da bi on znao da je to
            // obican znak, a ne kraj formata (kao apostrofi u Paskalu)

            num = get_num_for(pb, n, name); // Dohvata se broj za procitano ime
            if (num) {
                fprintf(output, "%s", num);    // Broj postoji, ispisi ga
            } else {
                fprintf(output, "[%s]", name); // U supr. vrati ime i zagrade
            }
        }
    }

    fclose(input);
    fclose(output);
}

/* -------------------------------------------------------------------------- */

// Test funkcija za pravljenje binarne datoteke sa imenikom
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
