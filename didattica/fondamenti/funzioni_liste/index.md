---
title: Gestione Liste
author: Francesco Bruschi
layout: page
---

Fino ad ora, gestire le liste è stato qualcosa di molto _fastidioso_, nell'accezione di _poco scalabile_. Ogni nuovo elemento aggiunto richiede di gestire un ulteriore livello di redirezione (`->`), e in breve tempo il tutto diventa intrattabile. Vedremo ora come usare il potere dell'induzione ricorsiva per liberarci da questa sofferenza.

Osservazione: non vi sembra che le liste abbiano qualcosa di inquietantemente _ricorsivo_?

Immaginiamo di dover realizzare una funzione che stampa gli elementi di una lista di caratteri. Ci viene passato il puntatore al primo nodo. Mi pare che potremmo fare così: stampiamo il carattere del nodo che ci viene passato, e poi stampiamo la lista che ci resta. Come facciamo ad ottenere la lista che ci resta? E' facile: prendiamo il puntatore al nodo successivo! Il puntatore al nodo successivo _identifica_ un'altra lista: precisamente la lista dei caratteri dopo quello corrente.
    
     |P0|-->|'c'||---+
                     |
     |P1|    ------->+---->|'i'||---->|'a'||---->|'o'||----->NULL

Nel caso sopra, al puntatore `P0` corrisponde la lista `['c','i','a','o']`, mentre al puntatore `P1` corrisponde la lista `['i','a','o']`.

Poniamoci allora il problema di come scrivere una funzione che stampi gli elementi di una lista. Ebbene, chiediamoci:

1. _se fossimo_ in grado di stampare una lista di lunghezza `N`, saremmo in grado di stampare anche una lista di lunghezza `N+1`?
2. siamo in grado di stampare una lista di lunghezza `0`?

Se ci sentiamo di rispondere 'sì' ad entrambe le domande sopra, allora siamo in grado di stampare qualsiasi lista!

Scriviamo quindi, per prima cosa, una funzione che ci dimostri che sappiamo rispondere alla domanda 2. Come facciamo a sapere che una lista è di lunghezza `0`? Semplice: il puntatore al primo nodo punterà a `NULL`!

Ecco allora la funzione che stampa la nostra lista:

{% highlight c %}

typedef struct nodo {char carattere; struct nodo* prossimo} nodo;

void print_lista(nodo *lista)
{
    if (lista->prossimo == NULL)
        printf ("\n");

    printf("%c",lista->carattere);
    print_lista(lista->prossimo);

}

{% endhighlight %}
