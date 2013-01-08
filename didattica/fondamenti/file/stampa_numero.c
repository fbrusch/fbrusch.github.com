#include <stdio.h>

int main()
{
    int numero;
    FILE* f;
    f=fopen("numero.dat","r");
    fread(&numero,sizeof(int),1,f);
    fclose(f);
    printf ("%i\n",numero);
}
