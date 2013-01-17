---
layout: page
author: Francesco Bruschi
title: Minimax
---

Per ora pubblico il link al codice python della mia implementazione di minimax, ma mi riprometto di scrivere entro breve qualche appunto di spiegazione.
Se capite tutto, potreste essere in grado di [salvare il mondo](http://www.youtube.com/watch?v=NHWjlCaIrQo).

[Codice](https://gist.github.com/4554768)

Ecco un minimo di istruzioni per farlo funzionare:

1) copiate e incollate il codice in un file (immagino che lo chiamiate `tictactoe.py`)
2) invocate python:

    shell> python

    Python 2.7.2 (default, Jun 20 2012, 16:23:33) 
    [GCC 4.2.1 Compatible Apple Clang 4.0 (tags/Apple/clang-418.0.60)] on darwin
    Type "help", "copyright", "credits" or "license" for more information.
    


3) da dentro python:

    [GCC 4.2.1 Compatible Apple Clang 4.0 (tags/Apple/clang-418.0.60)] on darwin
    Type "help", "copyright", "credits" or "license" for more information.

Importiamo le funzioni dal nostro file:

    >>> from tictactoe import *

Inizializziamo una partita (che è rappresentata con un array di righe di numeri)

    >>> board = [[0,0,0],[0,0,0],[0,0,0]]

Chiediamo di calcolare qual è la mossa migliore che dovrebbe fare il giocatore 1:

    >>> m = next_move(board,1)

`next_move` stampa il "punteggio" di tutte le possibili mosse:

    [(0, (0, 0, 1)), (0, (0, 1, 1)), (0, (0, 2, 1)), (0, (1, 0, 1)), (0, (1, 1, 1)), (0, (1, 2, 1)), (0, (2, 0, 1)), (0, (2, 1, 1)), (0, (2, 2, 1))]

Le mosse sono tutte equivalenti (se tutti e due i giocatori giocano al meglio, ci portano in un pareggio).

Vediamo la nostra funzione quale mossa sceglie (scrivendo il nome di una variabile e premendo `return` la shell di python ci stampa il valore di quella variabile)

    >>> m
    (0, 0, 1)

Ok, facciamo questa mossa:

    >>> make_move(board,m)
    [[1, 0, 0], [0, 0, 0], [0, 0, 0]]

Se volete far fare una mossa arbitraria, tipo far giocare il `2` in posizione 1,1:

    >>> make_move(board,(1,1,2))

