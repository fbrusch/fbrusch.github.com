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

Ok. Ora immaginiamo che ciascuna dei nostri _io paralleli_ controlli se lo schema di sudoku che si trova sotto gli occhi è valido oppure no. La regola è: chi si trova in mano uno schema _non valido_, cioè uno schema che non rispetta le regole del sudoku, si suicida. Dopo questo drammatico passo di selezione, la situazione degli universi paralleli sarà:


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
    
[...]

[Codice del sudoku](sudoku_in_classe.c)
