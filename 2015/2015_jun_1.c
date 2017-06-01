#include <ctype.h>
#include <stdbool.h> // bool, true, false
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALLOC_CHECK(p) if (!(p)) puts("Neuspesna alokacija"), exit(1)

/*
 * Proverava da li je rec sifrovana
 */
bool is_encrypted(char *word)
{
    bool enc;
    unsigned len = strlen(word), i;

    if (len < 3) {
        return false; // Sifrovana rec mora imati bar 3 znaka
    }

    // Proverava prvi, drugi i poslednji znak
    enc = isupper(word[0]) && word[1] == '@' && isupper(word[len-1]);

    for (i = 2; enc && i < len-1; ++i) {
        if (!isdigit(word[i])) { // Proverava da li je svaki znak u sredini cifra
            enc = false;
        }
    }

    return enc;
}

/*
 * Prvi nacin (ucitavanje rec po rec i obrada)
 */
int main(void)
{
    char *word, c;
    unsigned size;  // Umesto unsigned jos bolje size_t iz <stdlib.h>
    unsigned i = 0, n = 0, total = 0;

    word = malloc(size = 10);   // Ne treba sizeof(char) jer je to uvek 1
    ALLOC_CHECK(word);

    do {
        c = getchar();
        if (!isspace(c)) {
            word[i++] = c;      // Nije kraj reci, ubacuje se znak
            if (i == size) {
                word = realloc(word, size *= 2); // i realocira po potrebi
                ALLOC_CHECK(word);
            }
        } else {
            word[i] = '\0';     // Kraj reci, treba sprovesti obradu
            if (is_encrypted(word)) {
                ++n;    // Broj sifrovanih reci
            } else {
                printf("%s ", word);
            }
            ++total;    // Ukupan broj reci
            i = 0;  // Sledece se cita nova rec, indeks se vraca na 0
        }
    } while (c != '\n');

    // Konverzija u realni tip da ne bi doslo do gubitka tacnosti
    // Format %g pise broj kao 40 umesto 40.000000 (tacno koliko treba decimala)
    printf("\n%g%%\n", n * 100.0 / total);

    free(word);
    return 0;
}

/*
 * Drugi nacin (ucitavanje celog reda i razbijanje na reci sa strtok)
 */
int main(void)
{
    char *str, *word, c;
    unsigned size, len;
    unsigned i = 0, n = 0, total = 0;

    str = malloc(size = 10);
    ALLOC_CHECK(str);

    while ((c = getchar()) != '\n') {
        str[i++] = c;
        if (i == size) {
            str = realloc(str, size *= 2);
            ALLOC_CHECK(str);
        }
    }

    // http://www.cplusplus.com/reference/cstring/strtok/
    for (word = strtok(str, " "); word; word = strtok(NULL, " ")) {
        if (is_encrypted(word)) {
            ++n;
        } else {
            printf("%s ", word);
        }
        ++total;
    }

    printf("\n%g%%\n", n * 100.0 / total);

    free(str);
    return 0;
}
