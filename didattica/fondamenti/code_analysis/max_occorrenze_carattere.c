/*
notes: ''
suitable_for: [prima_prova, appello]
tags: [stringhe]
text:
    it: "Si indichi quale output produrrebbe l'esecuzinoe del seguente codice"
    en:
title: 'Calcolo del massimo delle occorrenze di un carattere in una stringa'
notes:
    it: |
        `f` calcola il numero delle occorrenze del carattere `b` nella stringa `a`
        `g` calcola il numero massimo delle occorrenze
    en:


*/

#include <stdio.h>

int f(char a[], char b)
{
    int i, n=0;
    for (i=0;a[i]!='\0';i++)
        if (a[i]==b) n++;
    return n;
}

char g(char a[])
{
    char c; int i,m=0;
    for (i=0;a[i]!='\0';i++)
        if (f(a,a[i])>m)
        { c=a[i]; m=f(a,a[i]);}
    return c;
}

int main()
{
    printf ("%c\n",g("quare id faciam"));
    printf ("%c\n",g("fortasse requiris"));
    printf ("%c\n",g("nescio, sed fieri sentior, et exrucior"));
}

