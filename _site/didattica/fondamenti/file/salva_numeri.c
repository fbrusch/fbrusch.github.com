#include <stdio.h>
#include "numeri.h"

int main()
{
    int numeri[LEN];
    int i;
    FILE* f;

    for (i=0;i<LEN;i++)
        scanf("%i",numeri+i);

    f=fopen("numeri.dat","w");
    fwrite(numeri,sizeof(int),LEN,f);
    fclose(f);
}
