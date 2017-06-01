#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LOW  10
#define HIGH 10000

#define SEED_RNG srand(time(NULL))
#define SQR(x)   (x)*(x)

/* Vraca pseudoslucajan ceo broj u intervalu [min, max] */
int rand_int(int min, int max)
{
	return rand() / (double)RAND_MAX * (max-min) + min;
}

/*
 * Proverava da li je n Fibonacijev broj.
 * Broj n pripada Fibonacijevom nizu (1, 1, 2, 3, 5, ...) ako je bar jedan od
 * izraza 5n^2 - 4 i 5n^2 + 4 koren nekog prirodnog broja (Bineova formula).
 */
int check_fib(int n)
{
	int a = 5*SQR(n) - 4, b = 5*SQR(n) + 4;
	int sqrt_a = sqrt(a), sqrt_b = sqrt(b);
	return SQR(sqrt_a) == a || SQR(sqrt_b) == b;
}

int main(void)
{
	int n, i;

	SEED_RNG;
	printf("Generisani broj je: %d\n", n = rand_int(LOW, HIGH));
	printf("Taj broj %s Fibonacijev\n", check_fib(n) ? "jeste" : "nije");

	for (i = 0; i < 1000000; ++i) {
		if (check_fib(i)) {
			printf("%d\n", i);
		}
	}

	return 0;
}