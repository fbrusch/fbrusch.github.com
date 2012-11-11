---
layout: post
title: "Hello World! "
description: "Your first C Program"
category: 
tags: ["C Code, Absolute Beginners"]
---
{% include JB/setup %}

Questo e' il mio primo post con Jekyll. Vorrei spiegare come scrivere il proprio primo programma in C.
Prima di tutto: aprite un editor.
Quindi: scrivete nell'editor il seguente codice:

    #include <stdio.h>
    
    int main()
    {
        printf("Hello World!\n");
    }

Salvate il file con il nome "hello.c"

A questo punto, lanciate i seguenti comandi da console:

    gcc hello.c -o hello
    ./prova

L'output del programma dovrebbe essere:
    
    Hello World!


Et voilà!

Che ne dite??
Funziona?


