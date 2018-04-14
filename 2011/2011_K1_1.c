#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LOW  10
#define HIGH 10000

#define SEED_RNG srand(time(NULL))
#define SQR(x)   ((x)*(x))

// Generiše pseudoslučajan ceo broj u opsegu [LOW, HIGH]
int random(void)
{
    return rand()/(RAND_MAX+1.0) * (HIGH-LOW+1) + LOW;
}

// Proverava da li je n Fibonačijev broj
// Broj n pripada Fibonačijevom nizu (1, 1, 2, 3, 5, ...) ako je bar jedan od
// izraza 5n²-4 i 5n²+4 kvadrat nekog prirodnog broja (Bineova formula)
int check_fib(int n)
{
    int a = 5*SQR(n)-4, b = 5*SQR(n)+4;
    int sqrt_a = sqrt(a), sqrt_b = sqrt(b);
    return SQR(sqrt_a) == a || SQR(sqrt_b) == b;
}

int main(void)
{
    SEED_RNG;
    int n;
    printf("Generisani broj je: %d\n", n = random());
    printf("Taj broj %s Fibonacijev\n", check_fib(n) ? "jeste" : "nije");

    for (int i = 0; i < 1000000; ++i) {
        if (check_fib(i)) {
            printf("%d\n", i);
        }
    }
}
