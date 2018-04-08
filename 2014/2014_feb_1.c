#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PHONEBOOK_FILE "imenik.dat"
#define INPUT_FILE     "ulaz.txt"
#define OUTPUT_FILE    "izlaz.txt"

#define NAME_LEN    31
#define NUM_LEN     11
#define MAX_ENTRIES 300

// Štampa gresku, prekida program
#define IO_ERROR(f) (perror(f), exit(1))

// Otvara fajl, vrši proveru, izlazi po potrebi
#define ASSIGN(p, f, m) if (!((p) = fopen(f, m))) IO_ERROR(f)
 
typedef struct entry {
    char name[NAME_LEN], num[NUM_LEN];
} Entry;

// Dovoljan je niz jer piše maks. 300 unosa, ne treba lista
typedef Entry Phonebook[MAX_ENTRIES];

int read_phonebook(Phonebook pb)
{
    int n;
    FILE *pb_file;

    ASSIGN(pb_file, PHONEBOOK_FILE, "rb");

    // Učitava zapise u niz, vraća broj uspešno pročitanih zapisa
    n = fread(pb, sizeof(Entry), MAX_ENTRIES, pb_file);

    fclose(pb_file);
    return n;
}

char *get_num_for(Phonebook pb, int n, char *name)
{
    int i;
    for (i = 0; i < n; ++i) {
        if (strcmp(pb[i].name, name) == 0) {
            return pb[i].num;
        }
    }
    return NULL;
}

void process_input(Phonebook pb, int n)
{
    FILE *input, *output;
    int c;
    char name[NAME_LEN], *num;

    ASSIGN(input, INPUT_FILE, "r");
    ASSIGN(output, OUTPUT_FILE, "w");

    while ((c = fgetc(input)) != EOF) {
        if (c != '[') {
            fputc(c, output);  // Ako znak nije [, samo ga prepisuje
        } else {
            // Čita najviše 30 znakova ili do prvog ] i pamti to u `name`
            fscanf(input, "%30[^]]]", name);

            num = get_num_for(pb, n, name);
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

int main(void)
{
    Phonebook pb;
    int n;

    n = read_phonebook(pb);
    process_input(pb, n);

    return 0;
}
