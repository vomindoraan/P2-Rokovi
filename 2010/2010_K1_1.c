#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LOW     1
#define HIGH    100
#define N_TRIES 10

#define SEED_RNG srand(time(NULL))

/* Vraca slucajan ceo broj u opsegu [LOW, HIGH] */
int rand100(void)
{
    return rand() / (double)RAND_MAX * (HIGH-LOW) + LOW;
}

int main(void)
{
    int r, i, t;

    SEED_RNG;
    r = rand100();
    printf("Slucajan broj je generisan, imate %d pokusaja:\n\n", N_TRIES);

    for (i = 0; i < N_TRIES; ++i) {
        scanf("%d", &t);
        if (t == r) {
            ++i;
            break;
        }
        printf("Vas broj je %s od trazenog\n\n", (t < r) ? "manji" : "veci");
    }

    printf("Broj pokusaja: %d\n", i);
    printf("Trazeni broj %s pogodjen!\n", (t == r) ? "je" : "nije");

    return 0;
}
