#include <stdio.h>


typedef struct nodo {char carattere; struct nodo* prossimo} nodo;


nodo *nuovo_nodo(char c)
{
    nodo *nuovo=malloc(sizeof(nodo));
    nodo->carattere=c;
    nodo->prossimo=NULL;
    return nodo;
}

void print_lista(nodo *lista)
{
    if (lista->prossimo == NULL)
        printf ("\n");

    printf("%c",lista->carattere);
    print_lista(lista->prossimo);

}


void append(node *list, char c)
{

}
