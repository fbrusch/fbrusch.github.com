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

struct nodo
{
    char dato;
    struct nodo *prossimo;
};

void stampa_lista(struct nodo *lista)
{
    if (lista==NULL)
    {
        printf ("\n");
        return;
    }

    printf ("%c",lista->dato);
    stampa_lista(lista->prossimo);
}

{% endhighlight %}

Proviamo ad applicare lo stesso concetto per scrivere una funzione che calcola la lunghezza di una lista. Il ragionamento è questo:

1. se la lista è vuota (cioè se il puntatore al primo elemento è `NULL`), la lunghezza è `0`
2. altrimenti, la lunghezza è `1` (l'elemento corrente) più la lunghezza della lista successiva al primo elemento.

Per comodità, ci riferiremo d'ora in poi al primo elemento della lista come alla _testa_, e al resto della lista come alla _coda_.


{% highlight c %}

int len(struct nodo *lista)
{
    if (lista==NULL)
        return 0;
    return 1 // lunghezza della testa (1)
        +len(lista->prossimo); // lunghezza della coda (len(lista->prossimo))
}

{% endhighlight %}

Ora cerchiamo di implementare la funzione `append` che tanto invidiamo ai nostri amici pythonisti. Il ragionamento, in questo caso, è:

1. se la _coda_ della lista è vuota (cioè se la lista è composta solo dalla _testa_), allora aggiungi direttamente il nuovo nodo alla testa
2. altrimenti, fai `append` del nuovo nodo sulla _coda_.

{% highlight c %}

void append(struct nodo *lista, char c)
{

    if (lista==NULL)

    if (lista->prossimo==NULL)
    {
        lista->prossimo=malloc(sizeof(struct nodo));
        (lista->prossimo)->dato=c;
        (lista->prossimo)->prossimo=NULL;
        return;
    }
    append(lista->prossimo, c);
}

{% endhighlight %}

Ora poniamoci finalmente il problema di stampare il contenuto della nostra lista al contrario. Anche qui possiamo avvalerci del ragionamento ricorsivo, in questo modo:

1. se la lista è vuota, non stampare niente
2. se la lista non è vuota, prendine la _coda_, stampala al contrario, e *poi* stampa la _testa_.

{% highlight c %}

void stampa_lista_contrario(struct nodo *lista)
{
    if (lista==NULL)
        return;
    stampa_lista_contrario(lista->prossimo);
    printf ("%c",lista->dato);
}

{% endhighlight %}

[Qui](nodo.c) trovate un esempio completo di utilizzo delle nostre funzioni...

### Implementazione iterativa
La ricorsione è un mezzo molto potente ed espressivo, e consente di risolvere alcuni problemi in modo estremamente elegante. Ricordiamo però che l'esecuzione di una funzione ricorsiva può essere anche molto onerosa. Ad esempio, la profondità di ricorsione della nostre funzioni è pari al numero degli elementi della lista: se vogliamo aggiungere un elemento in fondo ad una lista di 1.000.000 elementi con la nostra `append`, ci ritroveremo con un 1.000.000 di chiamate annidate, e con i corrispondenti record di attivazione in cima alla pila (vale la pena di notare che alcuni compilatori sono in grado di ottimizzare un particolare tipo di ricorsione, detta "[in coda](http://en.wikipedia.org/wiki/Tail_call)", in modo che questa `esplosione` sulla pila non avvenga).
Proviamo quindi ad implementare, senza ricorrere alla ricorsione (ahah), le funzioni di gestione delle liste viste sopra. Partiamo da quella forse più semplice: la `len`.
L'idea è questa: prendiamo una variabile, `i`, che utilizziamo in questo modo: inizialmente le assegnamo come valore la testa della lista (cioè, lo ricordiamo, l'indirizzo al primo elemento):

{% highlight c %}
int len(struct node *l)
{
    struct node *i;
    i=l;
    [...]

{% endhighlight %}

A questo punto ci troviamo in questa situazione:

    
    l---+
        |   
        +--->| ||---->| ||---->| ||----->NULL
        |
    i---|

se ora eseguiamo il seguente assegnamento:

{% highlight c %}

    i = i->prossimo;

{% endhighlight %}

la situazione diventa questa:

    l---+
        |   
        +--->| ||--+->| ||---->| ||---->NULL
                   |
    i--------------|

cioè `i` punta al secondo elemento. La strategia è quella di far avanzare `i`, fino a farlo puntare a `NULL`, e nel frattempo contare quanti salti si sono fatti. Riassumiamo tutto in un ciclo `for`:


{% highlight c %}

[...]
int lunghezza;
for (lunghezza=0, i=l;i!=NULL;i=i->prossimo)
    ;

{% endhighlight %}

A questo punto, quando il ciclo termina, in `lunghezza` c'è la lunghezza della lista, che possiamo ritornare.
asd


