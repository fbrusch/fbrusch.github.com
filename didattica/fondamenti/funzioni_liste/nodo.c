#include <stdio.h>
#include <stdlib.h>

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

int len(struct nodo *lista)
{
    if (lista==NULL)
        return 0;
    return 1+len(lista->prossimo);
}

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

void stampa_lista_contrario(struct nodo *lista)
{
    if (lista==NULL)
        return;
    stampa_lista_contrario(lista->prossimo);
    printf ("%c",lista->dato);
}


int main()
{
    struct nodo *l=NULL;

    append(l,'c');

    l=malloc(sizeof(struct nodo));
    l->dato='c';
    l->prossimo=NULL;

    char c;

    do
    {
        scanf("%c",&c);
        append(l,c);
    } while (c!='.');

    stampa_lista(l);
    stampa_lista_contrario(l);
    printf("\n");

    printf ("la lista e' lunga: %i\n",len(l));
}
