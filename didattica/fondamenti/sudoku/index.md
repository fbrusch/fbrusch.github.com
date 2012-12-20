---
layout: page
title: Sudoku, risolutori, e universi paralleli
comments: true
---

Ok, vogliamo risolvere il [sudoku](http://it.wikipedia.org/wiki/Sudoku), quello che troviamo nella pagina dell'enigmistica del giornale. Anzi, vogliamo farlo risolvere al calcolatore. Quindi, come abbiamo intuito, dovremo scrivere un programma che lo risolva. E, prima, ci converrà bene trovare un algoritmo.
Osservazione: il sudoku che troviamo normalmente sulle pagine di un giornale è composto da uno schema 9 per 9. Ora, ci chiediamo: cosa c'è di speciale nel numero 9? Potremmo definire schemi di sudoku 8 per 8? Un attimo di riflessione ci convince del fatto che potremmo variare la dimensione dello schema, a patto di utilizzare, per la dimensione del lato, un _quadrato perfetto_. In questo modo, è possibile formare i sottoquadrati. Quindi sono possibili sudoku di tante dimensioni, una per ciascun quadrato perfetto. Ed ecco la prima osservazione: nel ragionare sulla ricerca di una soluzione automatica, ci conviene considerare il caso dimensionalmente più gestibile, e cercare una soluzione parametrica rispetto alle dimensioni. In questo modo:
1. possiamo fare leva più facilmente sull'intuito
2. otteniamo una soluzione che è più generale, che vale per tutte le famiglie di sudoku, e che ci permetterà di stupire i nostri amici con improponibili schemi 25 per 25...

Ok, consideriamo quindi uno schema 4 per 4:

    +---+---++---+---+
    |   | 4 ||   | 2 |
    +---+---++---+---+
    | 2 |   || 1 |   |
    +===+===++===+===+
    |   | 2 ||   | 1 |
    +---+---++---+---+
    | 4 | 1 ||   | 3 |
    +---+---++---+---+

Utilizziamo questa convenzione: ci riferiamo alle caselle vuote con: `v0, v1...` dove `v0` è la prima casella vuota etc:


    +---+---++---+---+
    | v0| 4 ||   | 2 |
    +---+---++---+---+
    | 2 | v1|| 1 |etc|
    +---+---++---+---|
    +---+---++---+---+
    |   | 2 ||   | 1 |
    +---+---++---+---+
    | 4 | 1 ||   | 3 |
    +---+---++---+---+

Il nostro scopo è completare lo schema, cioè riempire tutte le caselle vuote rispettando le regole del gioco.
Ora, la domanda è: qual è il valore che dobbiamo mettere in `v0`? Attenzione: non lasciamoci ingannare dal fatto che, in questo caso semplice, il numero lo vediamo 'a occhio'. Dobbiamo riuscire a descrivere una procedura facilmente traducibile in linguaggio C.
Ebbene, partiamo con un approccio estremo, che ci richieda il minimo sforzo intellettivo, a un certo livello: vogliamo provare a mettere in `v0` qualsiasi cifra ammissibile, cioè una tra `{1,2,3,4}`. Immaginiamo di poter fare contemporaneamente tutte e quattro le scelte, e di creare quattro diversi universi paralleli: uno in cui abbiamo scelto `1`, uno in cui abbiamo scelto `2`, etc:

    + universo originario
    |
    +----v0=1
    |
    +----v0=2
    |
    +----v0=3
    |
    +----v0=4

Ok. Ora immaginiamo che ciascuna dei nostri _io paralleli_ controlli se lo schema di sudoku che si trova sotto gli occhi è valido oppure no. La regola è: chi si trova in mano uno schema _non valido_, cioè uno schema che non rispetta le regole del sudoku, _rinuncia_, e si autodissolve nello spirito cosmico. Dopo questo drammatico passo di selezione, la situazione degli universi paralleli sarà:


    + universo originario
    |
    +----v0=1
    |
    +----v0=3

In questi due universi, il problema è quale prossima mossa fare, cioè cosa mettere in `v2`. Ancora una volta, non facciamo ragionamenti troppo sofisticati, e proviamo con tutte le cifre:


    + universo originario
    |
    |(v0=1)
    +----+
    |    |
    |    +---(v0=1, v1=1)
    |    |
    |    +---(v0=1, v1=2)
    |    |
    |    +---(v0=1, v1=3)
    |    |
    |    +---(v0=1, v1=4)
    |
    |(v0=3)    
    +----+
         |
         +---(v0=3, v1=1)
         |
         +---(v0=3, v1=2)
         |
         +---(v0=3, v1=3)
         |
         +---(v0=3, v1=4)
    
Procedendo per selezioni e biforcazioni, prima o poi arriveremo ad un universo in cui tutte le caselle vuote sono state riempite. Se la soluzione è unica, rimarrà un clone di noi in un solo universo, e quello sarà il 'noi' che ha trovato la soluzione.

Ora, come facciamo ad implementare tutto questo in C?
Vedremo più avanti uno strumento (la programmazione multiprocesso) che implementa una semantica di esecuzione molto simile a quella dei nostri universi biforcanti. Per ora siamo soli. Come possiamo fare?
Potremmo utilizzare un ragionamento ricorsivo di questo tipo:
1. sono in grado di risolvere un sudoku in cui _tutte_ le caselle sono state assegnate? Beh, sì: controllo se tutte le regole sono state rispettate: se sì, il sudoku è già risolto, se no, non è risolvibile!
2. se devo risolvere un sudoku con `n` caselle vuote: prendo la prima casella vuota, ci metto il primo numero possibile, e provo a risolvere lo schema con `n-1` caselle vuote risultante. Se non ci riesco, provo con la cifra successiva. Se non ci riesco con nessuna cifra, il sudoku non è risolubile!

Il ragionamento delineato dai punti 1. e 2. è correttamente ricorsivo: c'è un caso base che so risolvere, e c'è un passo di riduzione che mi avvicina al caso base.

Una possibile implementazione, in C, potrebbe essere:

{% highlight c %}
int risolvi_sudoku(int s[DIM][DIM])
{
    int x,y;
    int i,j;
    int trovato_vuoto=0;

    /* cerca la prima casella vuota 
    /* alla fine del ciclo, se c'e' una casella vuota
       trovato_vuoto varra' 1, e le coordinate della casella
       saranno in x e in y */

    for (i=0;i<DIM;i++)
        for (j=0;j<DIM;j++)
            if (s[i][j]==0)
                if (trovato_vuoto==0)
                {
                    trovato_vuoto=1;
                    x=i;
                    y=j;
                }

    if (trovato_vuoto==0) // se lo schema e' completo
    {
        if (corretto(s) return 1); // se e' corretto hai risolto
        else return 0;             // altrimenti e' impossibile
    }

    for (i=1;i<=DIM;i++)
    {
        s[x][y]=i;
        if (risolvi_sudoku(s)!=0) return 1;
    }
    s[x][y]=0;
    return 0;
}

{% endhighlight %}

Nel codice sopra abbiamo immaginato di avere a disposizione una funzione, `corretto`, che controlla se una matrice passata è uno schema di sudoku corretto.
Il problema di questa soluzione è che controlliamo se uno schema è corretto solamente quando siamo arrivati in un universo 'terminale', cioè uno in cui tutte le caselle sono state riempite. In realtà noi potremmo scartare interi 'sottoalberi' di scelta: da uno schema incompleto in cui è violata una regola (c'è una ripetizione in una riga, in una colonna, o in un quadrante) non potrà mai venire fuori una soluzione corretta solo riempiendo altre caselle.
Possiamo fare qualcosa di molto più furbo così:

{% highlight c %}

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
        if (risolvi_sudoku(s)!=0) return 1;
    }
    s[x][y]=0;
    return 0;
}

{% endhighlight %}

Ora ci rimane solo da scrivere la funzione `corretto`, che è concettualmente banale.

La trovate, insieme a tutto il resto, [qui](sudoku_in_classe.c).
