#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 21
#define PROV_MEM(p) if (!p) printf("Neuspesna alokacija\n"), exit(1)

/*
// Unos kada je unapred poznat broj reči
char **unos(int *pm)
{
    printf("Uneti broj reci: ");
    scanf("%d%*c", pm);  // %*c proguta \n

    char **mat = calloc(*pm, sizeof *mat);  // Isto kao: sizeof(char*)
    PROV_MEM(mat);

    printf("Uneti reci:\n");
    for (int i = 0; i < *pm; i++) {
        mat[i] = calloc(N, sizeof **mat);  // Isto kao: sizeof(char)
        PROV_MEM(mat[i]);

        // Čitanje celog reda u string mat[i]        
        // fgets(mat[i], N, stdin);
        // mat[i][strlen(mat[i])-1] = '\0';  // Izbacuje \n

        // Čitanje celog reda u string mat[i]
        scanf("%[^\n]%*c", mat[i]);
    }

    return mat;
}
*/

/*
// Dinamički unos bez skraćivanja, sa inkrementalnim proširivanjem
char **unos(int *pm)
{
    int vel = 0;
    char **mat = NULL;

    printf("Uneti reci (prazan red za kraj):\n");
    for (int i = 0; 1; i++) {
        char str[N] = "";
        scanf("%[^\n]%*c", str);
        if (strlen(str) == 0)
            break;

        if (i == vel) {
            mat = realloc(mat, ++vel * sizeof *mat);
            PROV_MEM(mat);
        }

        mat[i] = calloc(N, sizeof **mat);
        strcpy(mat[i], str);
    }

    *pm = vel;
    return mat;
}
*/

// Dinamički unos sa skraćivanjem i optimalnim proširivanjem
char **unos(int *pm)
{
    int vel = 16;
    char **mat = calloc(vel, sizeof *mat);
    PROV_MEM(mat);

    printf("Uneti reci (prazan red za kraj):\n");
    int i;
    for (i = 0; 1; i++) {
        char str[N] = "";
        scanf("%[^\n]%*c", str);
        if (strlen(str) == 0)
            break;

        if (i == vel) {
            vel *= 2;
            mat = realloc(mat, vel * sizeof *mat);
            PROV_MEM(mat);
        }

        mat[i] = calloc(N, sizeof **mat);
        strcpy(mat[i], str);
    }

    vel = i;  // i je stvarna veličina matrice
    mat = realloc(mat, vel * sizeof *mat);
    // Ne mora da se proveri alokacija jer skraćivanje uvek uspeva

    *pm = vel;
    return mat;
}

void obrada(char **mat, int m)
{
    char br_poj[128] = { 0 };

    for (int i = 0; i < m; i++)
        for (int j = 0; j < strlen(mat[i]); j++) {
            char c = tolower(mat[i][j]);  // Mala i velika se gledaju isto
            br_poj[c]++;
        }

    int maks = br_poj[1];  // Broj pojavljivanja \0 se ne gleda
    for (int i = 2; i < 128; i++)
        if (br_poj[i] > maks)
            maks = br_poj[i];

    printf("Slovo/a sa najvise pojavljivanja:\n");
    for (int i = 1; i < 128; i++)
        if (br_poj[i] == maks)
            printf("%c ", i);
}

int main(void)
{
    int m;
    char **mat = unos(&m);
    obrada(mat, m);
    return 0;
}
