#include <stdio.h>
#include <stdlib.h>

void find_subarray(int *arr, int n, float k, int *pstart, int *plen)
{
    for (int len = n; len > 0; len--) {
        for (int i = 0; i <= n-len; i++) {
            float sum = 0;
            
            for (int j = 0; j < len; j++)
                sum += arr[i+j];
            
            if (sum / len >= k) {
                *pstart = i;
                *plen = len;
                return;
            }
        }
    }
    *pstart = -1;
    *plen = 0;
}

int main(void)
{
    puts("Uneti n:");
    int n;
    scanf("%d", &n);

    int *arr = calloc(n, sizeof *arr);
    if (!arr) {
        fputs("Neuspesna alokacija", stderr);
        return 1;
    }

    puts("Uneti niz:");
    for (int i = 0; i < n; i++)
        scanf("%d", arr+i);

    puts("Uneti k:");
    float k;
    scanf("%f", &k);

    int start, len;
    find_subarray(arr, n, k, &start, &len);

    puts("Najduzi podniz je:");
    for (int i = 0; i < len; i++)
        printf("%d ", arr[start+i]);
}
