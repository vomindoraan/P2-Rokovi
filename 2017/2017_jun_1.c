#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PIECES "KDTLSPO"
#define KNIGHT 'S'
#define EMPTY  'O'

#define ALLOC_CHECK(p) if (!(p)) fputs("Neuspesna alokacija", stderr), exit(1)

typedef struct {
    char **squares;
    int m, n;
} Board;

typedef struct {
    Board white, black;
} Chess;

Board read_board(int m, int n)
{
    Board board = { calloc(m, sizeof(char*)), m, n };
    ALLOC_CHECK(board.squares);

    for (int i = 0; i < m; i++) {
        board.squares[i] = malloc(n);
        ALLOC_CHECK(board.squares[i]);

        for (int j = 0; j < n; j++) {
            char c = getchar();
            if (!strchr(PIECES, c)) { // Trazi znak u stringu i vraca pokazivac
                j--;
                continue;
            }
            board.squares[i][j] = c;
        }
    }

    return board;
}

Chess read_chess(void)
{
    Chess chess;
    int m, n;

    puts("Uneti velicinu table:");
    scanf("%d%d", &m, &n);

    puts("Uneti bele figure:");
    chess.white = read_board(m, n);

    puts("Uneti crne figure:");
    chess.black = read_board(m, n);

    fseek(stdin, 0, SEEK_END); // Cisti ulaz od viska unosa
    return chess;
}

void free_chess(Chess chess) {
    for (int i = 0; i < chess.white.m; i++) {
        free(chess.white.squares[i]);
        free(chess.black.squares[i]);
    }
    free(chess.white.squares);
    free(chess.black.squares);
}

void check(Board board, int i, int j)
{
    if (i >= 0 && i < board.m &&
        j >= 0 && j < board.n &&
        board.squares[i][j] != EMPTY)
    {
        printf("[%d,%d] %c\n", i, j, board.squares[i][j]);
    }
}

void solve(Chess chess, int side) { // 1=white, 0=black
    Board player = side ? chess.white : chess.black,
          enemy  = side ? chess.black : chess.white;

    for (int i = 0; i < player.m; i++)
        for (int j = 0; j < player.n; j++)
            if (player.squares[i][j] == KNIGHT) {
                printf("\nSkakac [%d,%d] moze da pojede:\n", i, j);

                check(enemy, i-1, j-2); check(enemy, i-2, j-1); // Gore levo
                check(enemy, i-2, j+1); check(enemy, i-1, j+2); // Gore desno
                check(enemy, i+1, j+2); check(enemy, i+2, j+1); // Dole desno
                check(enemy, i+2, j-1); check(enemy, i+1, j-2); // Dole levo
            }
}

int main(void)
{
    Chess chess = read_chess();
    puts("Uneti boju [b/c] (podraz. c):");
    solve(chess, getchar() == 'b');
    free_chess(chess);
}

// Unos boje se moze bolje uraditi ovako (u tom slucaju solve prima 2x Board):
// while (1) {
//     puts("Uneti boju [b/c]:");
//     switch (getchar()) {
//     case 'b': solve(chess.white, chess.black); break;
//     case 'c': solve(chess.black, chess.white); break;
//     default:  puts("Greska, probajte ponovo"); continue;
//     }
//     break;
// }
