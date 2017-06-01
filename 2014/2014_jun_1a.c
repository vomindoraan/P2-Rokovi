#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool prost(int n) {
	int i;
	for (i = 2; i <= n/2; i++) {
		if (n % i == 0)
			return false;
	}
	return true;
}

void obrada(int **niz, int n){
    int i, j;
	for (i = 1; i < n; i++) {
		for (j = 1; j < n; j++) {
			if (i + j >= n && prost(niz[i][j])) {
				niz[i][j] = niz[n-1-j][n-1-i];
			}
		}
	}
}

int main(void){
	int **niz, n, i, j;
	printf("Unesite dimenziju matrice: ");
	scanf("%d", &n);

	niz= calloc(n, sizeof(int*));
	for (i=0; i<n; i++){
		niz[i]=calloc(n, sizeof(int));
		for(j=0; j<n; j++)
			scanf("%d", &niz[i][j]);
	}

	obrada (niz, n);
	for (i=0; i<n; i++){
		for(j=0;j<n;j++)
			printf("%2d ", niz[i][j]);
		printf("\n");
	}

	for (i = 0; i < n; i++) {
		free(niz[i]);
	}
	free(niz);
}