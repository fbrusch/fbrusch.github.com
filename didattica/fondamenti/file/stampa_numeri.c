#include <stdio.h>
#include "numeri.h"

int main()
{
    int numeri[LEN];
    int i;
    FILE* f;
    f=fopen("numeri.dat","r");
    fread(numeri,sizeof(int),LEN,f);
    fclose(f);
    for (i=0;i<LEN;i++)
        printf ("%i\n",numeri[i]);
}
