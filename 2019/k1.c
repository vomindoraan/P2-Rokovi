#include <stdio.h>

#define MAX_ARRAY_LENGTH 1000

int main(int argc, char const *argv[])
{
    while (1)
    {
        size_t array_size;
        unsigned max0 = 0, max1 = 0, max2 = 0;
        unsigned array[MAX_ARRAY_LENGTH];
        size_t i, j;

        scanf("%u", &array_size);
        if (array_size < 3)
            break;

        for (i = 0; i < array_size; i++)
            scanf("%u", &array[i]);
        
        for (i = 0; i < array_size; i++)
        {
            printf("%u", array[i]);
            if (i != array_size)
                putchar(' ');
        }

        putchar('\n');

        for (i = 0; i < array_size; i++)
        {
            size_t k;
            size_t removed_count = 0;
            for (j = i + 1, k = j; j < array_size; j++)
            {
                if (array[i] != array[j])
                    array[k++] = array[j];
                else
                    removed_count++;
            }
            
            array_size -= removed_count;
        }
        
        for (i = 0; i < array_size; i++)
        {
            printf("%u", array[i]);
            if (i != array_size)
                putchar(' ');
        }

        putchar('\n');

        for (i = 0; i < array_size; i++)
        {
            if (array[i] > max0)
            {
                max2 = max1;
                max1 = max0;
                max0 = array[i];
            }
            else if (array[i] > max1)
            {
                max2 = max1;
                max1 = array[i];
            }
            else if (array[i] > max2)
                max2 = array[i];
        }

        if (array_size >= 1)
            printf("%u\n", max0);
        if (array_size >= 2)
            printf("%u\n", max1);
        if (array_size >= 3)
            printf("%u\n", max2);
        else
            for (i = 0; i < 3 - array_size; i++)
                puts("x");
    }
    
    return 0;
}
