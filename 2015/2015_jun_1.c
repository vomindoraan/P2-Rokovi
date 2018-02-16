#include <ctype.h>
#include <stdbool.h>  // bool, true, false
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHECK_ALLOC(p) if (!(p)) puts("Neuspesna alokacija"), exit(1)

// Proverava da li je reč šifrovaa
bool is_encrypted(char *word)
{
    bool enc;
    unsigned len = strlen(word), i;

    if (len < 3) {
        return false;  // Šifrovana reč mora imati bar 3 znaka
    }

    // Proverava prvi, drugi i poslednji znak
    enc = isupper(word[0]) && word[1] == '@' && isupper(word[len-1]);

    for (i = 2; enc && i < len-1; ++i) {
        if (!isdigit(word[i])) {  // Proverava da li je svaki srednji znak cifra
            enc = false;
        }
    }

    return enc;
}

// Prvi način (učitavanje reč po reč i obrada)
int main(void)
{
    char *word, c;
    unsigned size;  // Umesto unsigned još bolje size_t iz <stdlib.h>
    unsigned i = 0, n = 0, total = 0;

    word = malloc(size = 10);  // Ne treba sizeof(char) jer je to uvek 1
    CHECK_ALLOC(word);

    do {
        c = getchar();
        if (!isspace(c)) {
            word[i++] = c;  // Nije kraj reči, ubacuje se znak ...
            if (i == size) {
                word = realloc(word, size *= 2);  // i realocira po potrebi
                CHECK_ALLOC(word);
            }
        } else {
            word[i] = '\0';  // Kraj reči, treba sprovesti obradu
            if (is_encrypted(word)) {
                ++n;  // Broj šifrovanih reči
            } else {
                printf("%s ", word);
            }
            ++total;  // Ukupan broj reči
            i = 0;  // Sledeće se čita nova reč, indeks se vraća na 0
        }
    } while (c != '\n');

    // Pretvaranje u realni tip da ne bi došlo do gubitka tačnosti
    // Format %g piše broj kao 40 umesto 40.000000 (tačno koliko treba decimala)
    printf("\n%g%%\n", n * 100.0 / total);

    free(word);
    return 0;
}

// Drugi način (učitavanje celog reda i razbijanje na reči sa strtok)
int main(void)
{
    char *str, *word, c;
    unsigned size, len;
    unsigned i = 0, n = 0, total = 0;

    str = malloc(size = 10);
    CHECK_ALLOC(str);

    while ((c = getchar()) != '\n') {
        str[i++] = c;
        if (i == size) {
            str = realloc(str, size *= 2);
            CHECK_ALLOC(str);
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
