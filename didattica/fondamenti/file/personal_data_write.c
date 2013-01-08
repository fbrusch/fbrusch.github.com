#include <stdio.h>
#include <string.h>
#include "dati.h"

int main()
{
    struct dati_personali dati;
    FILE* f;

    strcpy(dati.nome,"Francesco");
    strcpy(dati.cognome,"Bruschi");
    strcpy(dati.telefono,"123456");

    f = fopen("dati.dat","w");
    fwrite(&dati, sizeof(dati), 1, f);
    fclose(f);

}
