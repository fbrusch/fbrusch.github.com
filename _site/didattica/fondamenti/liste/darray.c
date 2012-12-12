#include <stdio.h>

int *enlarge(int *a, int old_size, int new_size)
{
    int *b=malloc(sizeof(int)*old_size);
    int i;
    for (i=0;i<old_size;i++)
        b[i]=a[i];
    free (a);
    return b;
}

