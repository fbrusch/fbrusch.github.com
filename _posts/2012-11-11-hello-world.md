---
layout: post
title: "Hello World! "
description: "Your first C Program"
category: 
tags: ["C Code, Absolute Beginners"]
---
{% include JB/setup %}

Questo e' il mio primo post con Jekyll. Considererò un problema di scottante attualità: scriver il proprio primo programma in C.
Tradizionalmente, il primo vagito in un nuovo linguaggio deve essere un gioioso omaggio all'universo che ci ospita.

Editing
-------

Prima di tutto: aprite un editor. Ovviamente vi consiglio `vi`, che potete invocare così:

    vi hello.c

Quindi: scrivete nell'editor il seguente codice:

    #include <stdio.h>
    
    int main()
    {
        printf("Hello World!\n");
    }

Salvate il file con il nome `"hello.c"` (per salvare, premete `ESC` per tuffarvi in modalità comandi, quindi `:wq`)

Compilazione
------------

A questo punto, lanciate i seguenti comandi da console:

    gcc hello.c -o hello
    ./prova

L'output del programma dovrebbe essere:
    
    Hello World!


Et voilà!

Che ne dite??
Funziona?


