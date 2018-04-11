#include <stdbool.h>
#include <stdio.h>

#define N_MAX 100

int main(void)
{
    int n;
    printf("Uneti duzinu niza: ");
    scanf("%d", &n);
    if (n < 1 || n > N_MAX) return 1;

    int array[N_MAX];
    printf("Uneti niz:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &array[i]);
        if (array[i] <= 0) {
            printf("Neispravan broj, ponoviti unos\n");
            i--;
        }
    }

    for (int i = 0; i < n; i++) {
        printf("\n%d = ", array[i]);
        bool plus = false;

        for (int j = 8 * sizeof array[i] - 1; j >= 0; j--) {
            int bit = 1 << j;
            if (array[i] & bit) {
                if (plus) printf(" + ");
                plus = true;
                printf("2^%d", j);
            }
        }
    }

    return 0;
}
