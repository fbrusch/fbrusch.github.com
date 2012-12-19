#include <stdio.h>

#define ORDER 3
#define DIM (ORDER*ORDER)

int controlla_riga(int m[DIM][DIM], int riga)
{
    int i;
    int trovati[DIM];

    for (i=0;i<DIM;i++)
        trovati[i]=0;

    for (i=0;i<DIM;i++)
        if (trovati[m[riga][i]])
            return 0;   // ho incontrato un numero
                        // gia' incontrato prima
        else
            trovati[m[riga][i]]=1;
    return 1;
}

int controlla_colonna(int m[DIM][DIM], int colonna)
{
    int i;
    int trovati[DIM];

    for (i=0;i<DIM;i++)
        trovati[i]=0;

    for (i=0;i<DIM;i++)
        if (trovati[m[i][colonna]])
            return 0;   // ho incontrato un numero
                        // gia' incontrato prima
        else
            trovati[m[i][colonna]]=1;
    return 1;
}

