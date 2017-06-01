#include <stdio.h>

/* Euklidov algoritam za najveceg zajednickog delioca */
int gcd(int a, int b)
{
	return (b == 0) ? a : gcd(b, a % b);
}

int main(void)
{
	int a, b, d;

	printf("Uneti dva pozitivna cela broja razdvojena razmakom:\n");
	scanf("%d %d", &a, &b);
	if (a <= 0 || b <= 0) {
		printf("Brojevi nisu pozitivni");
		return 1;
	}

	while ((d = gcd(a, b)) > 1) {
		a /= d;
		b /= d;
	}

	printf("Uzajamno proste vrednosti brojeva su:\n");
	printf("%d %d\n", a, b);

	return 0;
}
