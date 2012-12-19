#include <stdio.h>
#define ORDINE 3
#define DIM (ORDINE*ORDINE)

int no_doppioni(int a[DIM])
{
    int trovato[DIM];
    int i;
    for (i=0;i<DIM;i++)
        trovato[i]=0;

    for (i=0;i<DIM;i++)
        if (a[i]!=0)
            if (trovato[a[i]-1]==1)
                return 0;
            else
                trovato[a[i]-1]=1;
    return 1;
}

int riga_corretta(int s[DIM][DIM], int riga)
{
    int a[DIM];
    int i;
    for (i=0;i<DIM;i++)
        a[i]=s[riga][i];
    return no_doppioni(a);
}

int colonna_corretta(int s[DIM][DIM], int colonna)
{
    int a[DIM];
    int i;
    for (i=0;i<DIM;i++)
        a[i]=s[i][colonna];
    return no_doppioni(a);
}

int riquadro_corretto(int s[DIM][DIM], int riquadro)
{
    int x=(riquadro%ORDINE)*ORDINE;
    int y=(riquadro/ORDINE)*ORDINE;
    int i;
    int a[DIM];
    for (i=0;i<DIM;i++)
        a[i]=s[x+(i%ORDINE)][y+(i/ORDINE)];
    return no_doppioni(a);
}

int corretto(int s[DIM][DIM])
{
    int i;
    for (i=0;i<DIM;i++)
    {
        if (riga_corretta(s,i)==0) return 0;
        if (colonna_corretta(s,i)==0) return 0;
        if (riquadro_corretto(s,i)==0) return 0;
    }
    return 1;
}

int risolvi_sudoku(int s[DIM][DIM])
{
    int x,y;
    int i,j;
    int trovato_vuoto=0;

    if (corretto(s)==0) return 0;

    for (i=0;i<DIM;i++)
        for (j=0;j<DIM;j++)
            if (s[i][j]==0)
                if (trovato_vuoto==0)
                {
                    trovato_vuoto=1;
                    x=i;
                    y=j;
                }

    if (trovato_vuoto==0) return 1;

    for (i=1;i<=DIM;i++)
    {
        s[x][y]=i;
        if (risolvi_sudoku(s)) return 1;
    }
    s[x][y]=0;
    return 0;
}


int stampa_sudoku(int s[DIM][DIM])
{
    int i,j;

    for (i=0;i<DIM;i++)
    {
        for (j=0;j<DIM;j++)
            printf ("%i\t",s[i][j]);
        printf ("\n");
    }

}

int main()
{
    int m[DIM][DIM]={{4,1,3,2,5,6,7,8,9},
                     {0,0,0,0,0,0,0,0,0},
                     {0,0,0,0,0,0,0,0,0},
                     {0,0,0,0,0,0,0,0,0},
                     {0,0,0,0,0,0,0,0,0},
                     {0,0,0,0,0,0,0,0,0},
                     {0,0,0,0,0,0,0,0,0},
                     {0,0,0,0,0,0,0,0,0},
                     {0,0,0,0,0,0,0,0,0}};
    risolvi_sudoku(m);
    stampa_sudoku(m);
}
