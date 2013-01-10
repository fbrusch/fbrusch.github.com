---
layout: page
title: Strutture Dinamiche
author: Francesco Bruschi
---

Ora sappiamo come costruire array di dimensioni desiderate a runtime. Possiamo così scrivere programmi del tipo:

{% highlight c %}

int *a;
int n,i;

printf ("quanti numeri devo leggere?\n");
scanf ("%i",&n);
a = malloc(sizeof(int)*n);
for (i=0;i<n;i++)
    scanf("%i"a+i);

/* fai qualcosa con gli elementi di a */

{% endhighlight %}

Però gli array dinamici non sono ancora la struttura dinamica più flessibile che possiamo immaginare. Per esempio, linguaggi come Python offrono strutture che consentono di fare cose notevoli come queste:

{%highlight python %}

>>> a = [1,2,3]
>>> print a
[1, 2, 3]
>>> a.append(4)
>>> print a
[1, 2, 3, 4]

{% endhighlight %}


In questo esempio, `a` è un array dinamico, che viene inizializzato con un certo insieme di valori, e che può poi crescere a piacimento.
I vantaggi della disponibilità di una struttura dati di questo tipo sono evidenti: non è necessario prevedere, al momento dell'allocazione, la quantità di memoria che servirà per contenere i dati, perché questa si può adattare all'occorrenza.

Prima di vedere se riusciamo ad ottenere la flessibilità degli  array di Python in C, consideriamo un altro approccio alla dinamicità delle strutture dati nel nostro amato linguaggio.
Quello che potremmo fare è una cosa del genere: immaginiamo di voler memorizzare un testo scritto dall'utente in un array. Non sappiamo quanto sarà lungo il testo. Immaginiamo questa situazione: vogliamo chiedere in input all'utente una sequenza di caratteri che rappresenti una frase in lingua italiana. La frase è una sequenza di caratteri, terminata da un carattere _punto_ `'.'`. 

Cominciamo con il dichiarare una lunghezza iniziale:

{%highlight c %}
#define DIM 16

[...]

int *text;
int i;
char c:
[...]

text = malloc(sizeof(char)*DIM);
i=0;
do 
{
    scanf ("%c",&c);
    text[i++]=c;
} while (c!='.' && i<DIM);

{% endhighlight %}

Il codice sopra dimensiona un array `a` in grado di memorizzare `DIM` caratteri e poi, nel ciclo `for`, chiede in input `DIM` caratteri. Cosa succede se, alla fine del ciclo l'utente non ha ancora immesso il fatidico carattere finale `'.'`?
Lo spazio inizialmente allocato è finito, cosa si può fare?
Una soluzione potrebbe essere: allochiamo una porzione di memoria più grande, copiamo i dati inseriti fin qui nella nuova zona di memoria, e ricominciamo a memorizzare i caratteri dal valore di dell'indice `i` al quale ci eravamo fermati:

{% highlight ruby %}

tmp = malloc(sizeof(int)*(DIM*2)); /* alloco */

for (j=0;j<DIM;j++)                /* copio i dati */
    tmp[j]=text[j];     

free(text);                        /* libero la zona di memoria vecchia */
text = tmp;                        /* cambio il valore di text: d'ora in poi si riferira'
                                      alla nuova zona di memoria */

{% endhighlight %}

Potremmo concentrare le operazioni di reallocazione in una funzione di questo tipo:

{% highlight c %}

#include <stdio.h>

int *enlarge(int *a, int old_size, int new_size)
{
    int *b=malloc(sizeof(int)*old_size);
    int i;
    for (i=0;i<old_size;i++)
        b[i]=a[i];
    free (a);
    return b;
}

{% endhighlight %}

La funzione si userebbe in questo modo: quando vogliamo spostare i dati presenti in memoria a partire dall'indirizzo a cui punta `text` in una zona più grande, possiamo fare così: 
{% highlight c %}
text = enlarge(text, DIM, 2*DIM)
{% endhighlight %}

Questa soluzione però presenta dei problemi, il più notevole dei quali è che, ad ogni 'enlargement', dobbiamo travasare tutti i dati dalla zona vecchia a quella nuova, e questa è un'operazione che può diventare molto costosa. Per minimizzare il numero di travasi potremmo allocare ogni volta molta memoria, ma allora al limite ricadremmo nel caso di array statici sovradimensionati. 

<!--Esiste una soluzione che ci consente di far crescere la memoria allocata in modo molto più continuo con le nostre esigenze. Vediamo di che si tratta...-->
<!--Rispetto al problema di sopra, immaginiamo di voler utilizzare una struttura che cresca ad ogni carattere che aggiungiamo...-->

<!--(liste etc ogni carattere che aggiungiamo...-->

<!--(liste, s etc, fino al-->
