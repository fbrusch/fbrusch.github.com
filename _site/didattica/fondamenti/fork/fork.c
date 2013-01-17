#include <stdio.h>
#include <unistd.h>
#define LEN 4

int main()
{
    int pid;
    int a[LEN];
    int i;
    int somma;

    for (i=0;i<LEN;i++)
        if (fork())
            a[i]=0;
        else
            if (fork())
                a[i]=1;
            else
                a[i]=2;

    somma=0;
    for (i=0;i<LEN;i++)
        somma+=a[i];

    if (somma==4)
    {
        for (i=0;i<LEN;i++)
            printf ("%i,",a[i]);
        printf ("\n");
    }
}


