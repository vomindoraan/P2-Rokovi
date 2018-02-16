#include <stdio.h>
#include <stdlib.h>

#define CHECK_ALLOC(p) if (!(p)) printf("Neuspesna alokacija\n"), exit(1)

char **read(int m, int n)
{
    char **mat = calloc(m, sizeof *mat);
    CHECK_ALLOC(mat);

    for (int i = 0; i < m; i++) {
        mat[i] = calloc(n, sizeof **mat);
        CHECK_ALLOC(mat[i]);

        for (int j = 0; j < n; j++)
            do {
                mat[i][j] = getchar();
            } while (!strchr("KDTLSPO", mat[i][j]));
    }

    return mat;
}

void solve(char **mat1, char **mat2, int m, int n)
{
    int di[] = { -1, -2, -2, -1, +1, +2, +2, +1 },
        dj[] = { -2, -1, +1, +2, +2, +1, -1, -2 };

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            if (mat1[i][j] == 'S') {
                printf("\nSkakac [%d,%d] moze da pojede:\n", i, j);

                for (int k = 0; k < 8; k++) {
                    int x = i + di[k], y = j + dj[k];
                    if (x >= 0 && x < m && y >= 0 && y < n && mat2[x][y] != 'O')
                        printf("[%d,%d] %c\n", x, y, mat2[x][y]);
                }
            }
}

void delete(char **mat, int m)
{
    for (int i = 0; i < m; i++)
        free(mat[i]);
    free(mat);
}

int main(void)
{
    printf("Uneti velicinu table: ");
    int m, n;
    scanf("%d%d", &m, &n);

    printf("Uneti bele figure:\n");
    char **white = read(m, n);

    printf("Uneti crne figure:\n");
    char **black = read(m, n);

    printf("Uneti boju [b/c]: ");
    switch (getchar(), getchar()) {  // Guta '\n' viška
    case 'b': solve(white, black, m, n); break;
    case 'c': solve(black, white, m, n); break;
    }

    delete(white, m);
    delete(black, m);
}
