#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LOW     1
#define HIGH    100
#define N_TRIES 10

#define SEED_RNG srand(time(NULL))

// Generiše pseudoslučajan ceo broj u opsegu [LOW, HIGH]
int rand100(void)
{
    return rand()/(RAND_MAX+1.0) * (HIGH-LOW+1) + LOW;
}

int main(void)
{
    SEED_RNG;
    int r = rand100(), t;
    printf("Slucajan broj je generisan, imate %d pokusaja:\n\n", N_TRIES);

    for (int i = 0; i < N_TRIES; ++i) {
        scanf("%d", &t);
        if (t == r) break;
        printf("Vas broj je %s od trazenog\n\n", (t < r) ? "manji" : "veci");
    }

    printf("Broj pokusaja: %d\n", i+1);
    printf("Trazeni broj %s pogodjen!\n", (t == r) ? "je" : "nije");
}
