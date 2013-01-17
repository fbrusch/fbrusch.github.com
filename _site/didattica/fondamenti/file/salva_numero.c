#include <stdio.h>

int main()
{
    FILE* f;
    int numero;

    scanf ("%i",&numero);

    f=fopen("numero.dat","w");
    fwrite(&numero,sizeof(int),1,f);
    fclose(f);
}
