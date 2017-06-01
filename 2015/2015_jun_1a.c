#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int sifrovana(char *rec)
{
    int len = strlen(rec);
    int res = isupper(rec[0]) && rec[1] == '@' && isupper(rec[len-1]), i;
    for (i = 2; i < len-1; ++i) {
        if (!isdigit(rec[i])) {
            res = 0;
            break;
        }
    }
    return res;
}

int main(void)
{
    char *rec, c;
    int vel, i = 0, br_sif = 0, br_reci = 0;

    rec = malloc(vel = 10);
    do {
        c = getchar();
        if (c == ' ' || c == '\n') {
            rec[i] = '\0';
            if (sifrovana(rec)) {
                br_sif++;
            } else {
                printf("%s ", rec);
            }
            br_reci++;
            i = 0;
        } else {
            rec[i++] = c;
            if (i == vel) {
                rec = realloc(rec, vel *= 2);
            }
        }
    } while (c != '\n');
    free(rec);

    printf("\n%g%%\n", br_sif / (double)br_reci * 100);

    return 0;
}
