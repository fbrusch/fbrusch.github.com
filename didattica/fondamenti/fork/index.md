---
title: Uno, Nessuno, Centomila
author: Francesco Bruschi
layout: page
---

Consideriamo questo problema: prendiamo tutte le possibili sequenze di quattro numeri appartenenti all'insieme `{0,1,2,3}`. Esempi di queste seguenze: `0,1,2,0`,`1,1,1,2`,`2,0,2,0`. Vogliamo stampare tutte le sequenze di questo tipo, per le quali la somma sia 4.
Una soluzione potrebbe consistere in un annidamento profondo di cicli:
{% highlight c %}
for (i=0;i<4;i++)
    for (j=0;j<4;j++)
        for (h=0;h<4;h++)
            for (k=0;k<4;k++)
                if (h+k+i+j==5)
                    printf ("%i,%i,%i,%i\n",i,j,k,h);
{% endhighlight %}

La soluzione proposta, però ha un po' di problemi, il più notevole dei quali è che _non scala_: se vogliamo allungare la sequenza, dobbiamo aggiungere "a mano" nel codice un altro ciclo.
Cogliamo l'occasione per fare la conoscenza con uno paradigma di programmazione molto potente: la [programmazione non deterministica](http://en.wikipedia.org/wiki/Nondeterministic_programming).
La cosa funziona più o meno così: ogni volta che, in un programma, dobbiamo valutare più opzioni, _le valutiamo tutte_! In che modo?
Proviamo a rappresentare il nostro problema in maniera diversa. Rappresentiamo la nostra sequenza con un array, in questo caso particolare di dimensione 4 (ma immaginiamo che la dimensione possa variare).
Proviamo a descrivere una possibile soluzione con questa metafora: per considerare _tutte_ le possibili sequenze di lunghezza 4 dei numeri `{0,1,2}`, consideriamo in sequenza ogni posizione dell'array `{0,1,2,3}`. Cominciamo dalla prima posizione, quella con indice `0`. Quante diverse opzioni abbiamo per mettere una cifra in questa posizione? Quattro. Bene, scegliamole tutte! In che modo: immaginiamo di _quadruplicare_ il nostro programma in esecuzione in quattro processi, in tutto e per tutto uguali, tranne che per il fatto che ognuno ha scelto una prima cifra diversa. A questo punto abbiamo quattro processi in esecuzione `P0,P1,P2,P3`. Ciascuno di questi processi ora deve scegliere una seconda cifra: ebbene, ciascuno si quadruplicherà e sceglierà di nuovo tutte le cifre. Alla fine di questa seconda ondata di clonazioni avremo sedici processi, che chiamiamo arbitrariamente: `P00,P01,P10,...,P33`.
Man mano che dobbiamo fare scelte, il numero di universi paralleli aumenta. Alla fine, quando tutti hanno fatto tutte le scelte, succede questo: ogni processo guarda il proprio array, ne somma gli elementi, e vede se il risultato è 4. In questo caso, il processo stampa il contenuto dell'array, altrimenti no.
Come si può implementare questo bizzarro comportamento, in C? Esistono molti modi diversi. (Entra `fork`.)

##Doppelgänger
I sistemi operativi Unix offrono una primitiva, la `fork`, che può essere invocata anche in un programma C, che consente di creare una copia (quasi) esatta del processo in esecuzione.
Vediamo subito un esempio:

{% highlight c %}

#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("prima di fork()\n");
    fork();
    printf("dopo fork()\n");
}

{% endhighlight %}

L'esecuzione di questo codice produce questo output:

    prima di fork()
    dopo fork()
    dopo fork()

Cosa fa, [`fork`](http://www.science.unitn.it/~fiorella/guidac/guidac096.html)?
_Sdoppia_ il processo in esecuzione, creando un processo quasi identico, chiamato processo _figlio_. Come fa, ciascuna delle due copie, a capire se è il padre oppure il figlio? La fork crea due processi identici (stesso codice, stesso valore del program counter, stesso valore di tutte le variabili e del contenuto della memoria) tranne che per un piccolo particolare: il valore di ritorno! Il figlio vede la fork ritornare il valore `0`, mentre il padre vede un valore diverso da `0` (in particolare, il padre si vede ritornare il _process id_ del figlio, cioè un valore che identifica univocamente il processo figlio).
Giocando sul valore di ritorno della `fork` possiamo differenziare il comportamento di padre e figlio:


{% highlight c %}

pid = fork();
if (pid==0)
    printf ("figlio\n");
else
    printf ("padre\n");

{% endhighlight %}

Output:

    padre
    figlio

Ecco come utilizzare la fork per implementare il comportamento non deterministico descritto sopra:

{% highlight c %}

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


{% endhighlight %}

Ed ecco l'output:

    1,1,2,0,
    2,0,0,2,
    1,1,1,1,
    0,2,0,2,
    1,1,0,2,
    2,2,0,0,
    1,2,0,1,
    0,0,2,2,
    1,0,1,2,
    0,2,2,0,
    1,2,1,0,
    2,1,1,0,
    0,1,1,2,
    2,0,1,1,
    2,0,2,0,
    1,0,2,1,
    2,1,0,1,
    0,2,1,1,
    0,1,2,1,



