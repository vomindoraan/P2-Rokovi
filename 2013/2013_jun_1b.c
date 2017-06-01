#include <math.h>
#include <stdio.h>

#define MAX 100

typedef struct tacka {
    float x, y, z;
} Tacka;

float razdaljina(Tacka t1, Tacka t2)
{
    return sqrt(pow(t1.x-t2.x, 2) + pow(t1.y-t2.y, 2) + pow(t1.z-t2.z, 2));
}

float nadji_tacke(int n, Tacka niz[], int *idx1, int *idx2)
{
    float razd = 0;
    int i, j;

    for (i = 0; i < n-1; ++i) {
        for (j = i+1; j < n; ++j) {
            int nova_razd = razdaljina(niz[i], niz[j]);
            if (nova_razd >= razd) {
                *idx1 = i;
                *idx2 = j;
                razd = nova_razd;
            }
        }
    }

    return razd;
}

int main(void)
{
    Tacka niz[MAX];
    int n, i, idx1, idx2;
    float max_razd;

    scanf("%d", &n);
    if (n < 1 || n > MAX) {
        return 1;
    }

    for (i = 0; i < n; ++i)
        scanf("%f%f%f", &niz[i].x, &niz[i].y, &niz[i].z);
    
    max_razd = nadji_tacke(n, niz, &idx1, &idx2);

    printf("Maks. razdaljina = %f\nidx1 = %d\nidx2 = %d\n",
           max_razd, idx1, idx2);
}