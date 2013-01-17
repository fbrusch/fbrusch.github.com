#include <stdio.h>
#include <stdlib.h>
#include "dati.h"

int main()
{
    struct dati_personali dati;
    FILE *f;

    f = fopen("dati.dat","r");
    fread(&dati,sizeof(dati),1,f);
    fclose(f);
    printf ("Nome: %s\n",dati.nome);
    printf ("Cognome: %s\n",dati.cognome);
    printf ("Numero di telefono: %s\n",dati.telefono);
}
