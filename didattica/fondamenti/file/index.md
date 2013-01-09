---
title: Verba volant, Scripta manent
tags: file, persistenza
author: Francesco Bruschi
layout: page

---

Ok: abbiamo raccolto tutti i dati che vogliamo elaborare dal nostro utente, oppure lo schema del sudoku, oppure qualsiasi altra cosa. Tra poco è ora di spegnere il computer,e tutti i [dati si perderanno](http://www.youtube.com/watch?v=Y3WamQPEQbM). La memoria di cui abbiamo tanto parlato, quella che usiamo per memorizzare il contenuto delle variabili, difatti, è _volatile_: ritiene l'informazione fino a quando è alimentata elettronicamente. Non appena l'alimentazione viene tolta, i condensatori che con la loro tensione rappresentano gli `0` e gli `1` che utilizziamo per codificare l'informazione si svuotano tutti, e la festa finisce. Non c'è niente che possiamo fare, se vogliamo scongiurare questo oblio? Se vogliamo lasciare una traccia di quello che è successo, se vogliamo poter continuare alla prossima accensione qualcosa che abbiamo lasciato a metà, insomma: se vogliamo _salvare_ i nostri dati? Ebbene sì: quello che possiamo possiamo fare e' di scrivere i nostri dati su un supporto _non volatile_, cioè un supporto in cui l'informazione non vada persa allo spegnimento. Supporti di questo tipo sono:dischi fissi, chiavette usb, cd-rom etc. 
E' anche possibile che, nel futuro, la memoria RAM, quella che usiamo per memorizzare le variabili utilizzate dai programmi in esecuzione, verrà realizzata con tecnologie non volatili, e quindi potremo vedere programmi che continuano a girare tra accensioni e spegnimenti senza fare una piega, ma il problema di scegliere quali dati perdere con la terminazione diun programma e quali tenere potrebbe restare (se la tecnologia ci consentirà di avere quantità ingenti di memoria a bassissimo costo lo scenario potrebbe essere ancora diverso...)
Ma viviamo nel presente: oggi la RAM è perlopiù volatile, e se vogliamo rendere qualche dato permanente, dobbiamo farlo esplicitamente. L'interfaccia che abbiamo a disposizione per rendere i dati permanenti è costruita attorno al concetto di _file_. Cos'è un _file_? E' molto semplice: un file è una _sequenza di byte_ con un nome. Ad esempio, il file sul quale è registrato questo documento comincia così:

    2d 2d 2d 0a 74 69 74 6c 65 3a 20 56 65 ...

(Ogni coppia di caratteri rappresenta un byte in formato esadecimale).

Che cosa possiamo fare, con un file?
Possiamo:
1. crearlo
2. aggiungere una sequenza di byte in fondo
3. aprirne uno esistente
4. leggere una sequenza di byte
5. sovrascrivere un byte in una certa posizione

Sembra poco, ma è abbastanza per fare molte cose. In particolare, è abbastanza per _salvare e caricare_ porzioni della memoria, cosa che ci consente di salvare e ricaricare dati presenti nelle variabili.

Cominciamo con il problema più semplice che ci può venire in mente: scrivere un programma che chieda un numero all'utente, e che lo memorizzi su un file, in modo che possa essere caricato in seguito, da un altro programma, e stampato.

### Creare un file
Come si fa a creare un nuovo file? La libreria C standard ci offre la funzione [`fopen`](http://it.wikibooks.org/wiki/C/Appendice/Librerie_standard/stdio.h#fopen.28.29).
`fopen` riceve in ingresso due parametri: una stringa, che rappresenta il nome del file da aprire, e un'altra stringa, che rappresenta la _modalità_, cioè l'informazione di quello che vogliamo fare con il file (se scriverci sopra, leggere, etc..). `fopen` restituisce un valore che chiamiamo _descrittore del file_, e che ci serve per riferici al file con le funzioni che lo manipolano (sarà chiaro poco più avanti cosa questo vuol dire). Qual è il tipo di dato del descrittore? Un intero? Una stringa? Nossignore: è un tipo di dato appositamente definito, nel file `stdio.h`, che si chiama `FILE`. Un descrittore ad un file è un puntatore ad una struttura di tipo `FILE`, e quindi si dichiarerà così:

{% highlight c %}
FILE *f;
{% endhighlight %}

Immaginiamo di voler aprire un file dove mettere il nostro numero. Chiamiamolo `numero.dat`. Faremo così:

{% highlight c %}
    
f = fopen("numero.dat","w");

{% endhighlight %}

La `"w"` come modalità vuol dire che sul file vorremo scrivere.
Ora chiediamo all'utente il numero:

{% highlight c %}

scanf ("%i",&numero);

{% endhighlight %}

Ok, ora in `numero` c'è il numero inserito dall'utente. Come facciamo a scriverlo? Attenti bene, il segreto è questo: _dobbiamo copiare la porzione di memoria che contiene il numero `num` sul file_. La libreria standard ci fornisce qualcosa che fa esattamente al caso nostro: la funzione [`fwrite`](http://it.wikibooks.org/wiki/C/Appendice/Librerie_standard/stdio.h#fwrite.28.29).

Il prototipo di `fwrite` è il seguente:

{% highlight c %}
size_t fwrite(const void * data, size_t size, size_t count, FILE* stream);
{% endhighlight %}

Soffermiamoci un attimo su questo prototipo, considerando ad uno ad uno i suoi parametri:

    const void * data

Il primo parametro è un puntatore (`*`) ad un dato di tipo `void`: questo significa che `fwrite` non si interessa al tipo dei dati che vogliamo scrivere sul disco (se avessimo avuto un parametro del tipo `const int * data` avrebbe voluto dire che stavamo considerando degli interi, ad esempio...). Il modificatore `const`, invece, significa che `fwrite` si impegna a non modificare la memoria alla quale punta `data`, e questo ha senso: `fwrite` accederà alla memoria solo per leggere dei dati e scriverli su disco, e possiamo stare tranquilli che i dati in memoria non saranno modificati.

    size_t size

Questo parametro rappresenta la dimensione del singolo blocco che vogliamo scrivere su disco. Nel nostro caso, sarà il numero di parole di memoria con cui è rappresentato un intero. E quante sono queste parole? Ma `sizeof(int)`, naturalmente!

    size_t count

Questo parametro rappresenta il numero di blocchi che vogliamo copiare dalla memoria al file. E' un parametro molto utile quando vogliamo copiare interi array. Nel nostro caso, qui passeremo un `1`, visto vogliamo scrivere un solo intero.

    FILE* stream

Qui è dove diciamo a `fwrite` su quale file vogliamo scrivere (il _descrittore_ di poco fa).
Siamo pronti per scrivere l'invocazione a `fwrite` che memorizza il nostro numero sul file appena aperto:

    fwrite(&n, sizeof(int), 1, f);

Et voilà! I byte che codificano il numero intero alla locazione `&n` sono ora copiati sul file `numero.dat`.

Ora si tratta di leggerli...

Per leggerli, possiamo basarci sulla funzione simmetrica di `fwrite`: [`fread`](http://linux.about.com/library/cmd/blcmdl3_fread.htm)

{% highlight c %}

size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);

{% endhighlight %}

Il codice del programma che legge il numero che abbiamo scritto nel file e lo stampa lo trovate qui: [stampa_numero](stampa_numero.c)

Il codice per salvare il numero su file invece è: [salva_numero](salva_numero.c)

###File di testo (ASCII)

Nell'esempio precedente, la sequenza di byte presente nel file `numero.dat` rappresenta un numero intero.
Ci sono file nei quali, invece, ogni byte rappresenta un carattere ASCII. Un esempio è [questo](ofrati.txt). Come forse i più raffinati culturalmente avranno notato, il testo contiene un pedestre errore di trascrizione. Come possiamo correggerlo? 
Poniamoci questo obiettivo: vogliamo trascrivere il testo in un altro file, del tutto uguale, ma in cui "bruchi" sia stato sostituito con "bruti".
Tra tutte le innumerevoli possibili soluzioni, vi propongo questa: prendiamo il file originario, lo copiamo in memoria, in una stringa; dopodiché lo scandiamo, carattere per carattere, e trascriviamo ogni carattere in un file destinazione, fino a quando ci imbattiamo nella parola incriminata ("bruchi"): a questo punto, sul file destinazione scriviamo la parola corretta ("bruti"), nella copia in memoria saltiamo la parola incriminata, e continuiamo sereni.

Ok, cominciamo...

Prima di tutto: 

Q: Quanta memoria ci serve, per contenere tutto il file? 

A: Beh, ci servono tanti `char` quanti sono quelli nel file. Visto che nel file ogni carattere è memorizzato con un byte, ci servono tanti `char` quanti sono i byte nel file

Q: Fantastico. Ma: come faccio a sapere quanti byte occupa il file?

A: Uso il seguente trucchetto: apro il file, sposto il puntatore di scrittura alla fine, e vedo quanto è distante dall'inizio. Per fare questo mi servo di due funzioni della libreria `stdio`: [`fseek`](http://www.acm.uiuc.edu/webmonkeys/book/c_guide/2.12.html#fseek) e [`ftell`](http://www.acm.uiuc.edu/webmonkeys/book/c_guide/2.12.html#ftell)

`fseek`, in particolare, mi consente di spostarmi nel file, specificando un _offset_ e una _posizione di riferimento_, che può essere: l'inizio del file (`SEEK_SET`), la posizione corrente (`SEEK_CUR`), oppure la fine del file (`SEEK_END`). quindi:

{% highlight c %}
fseek(f, 0, SEEK_END);
{% endhighlight %}

ci posiziona, nel file, alla fine (a 0 byte dalla fine).
A questo punto, `ftell(f)` ci dice a quanti byte siamo dall'inizio, quantità che corrisponde alla lunghezza del file:

{% highlight c %}
len=ftell(f);
{% endhighlight %}

Per riposizionarci all'inizio del file (dobbiamo ancora rileggerlo), usiamo la funzione [`rewind`](http://www.acm.uiuc.edu/webmonkeys/book/c_guide/2.12.html#rewind).

A questo punto, possiamo allocare la memoria che ci serve:
{% highlight c %}
    testo=malloc(sizeof(char)*(len+1));
{% endhighlight %}

(il `+1` serve per fare spazio al terminatore di stringa).

Leggiamo il file e mettiamo il contenuto nella memoria allocata:

{% highlight c %}
fread(testo,sizeof(char),len,f);
testo[len]='\0';
{% endhighlight %}

Apriamo il file di destinazione:

{% highlight c %}
dest=fopen("corretto.txt","w");
{% endhighlight %}

Ora immaginiamo di avere una funzione, `is_inizio_parola(char* text, char* parola)`, che restituisce `1` se la stringa a cui punta `text` comincia con la stringa a cui punta `parola`. Se avessimo questa funzione, il seguente ciclo salverebbe la stringa contenuta in `testo` sul file `dest`, sostituendo ogni occorrenza della stringa `sbagliata` con la stringa `corretta`:

{% highlight c %}
for (i=0;i<len;i++)
{
    if(is_inizio_parola(&testo[i],sbagliata)==0)
        fwrite(&testo[i],sizeof(char),1,dest);
    else
    {
        fwrite(corretta,sizeof(char),strlen(corretta),dest);
        i+=strlen(sbagliata)-1;
    }
}
{% endhighlight %}

La funzione `is_inizio_parola` si può implementare così:

{% highlight c %}
int is_inizio_parola(char* testo, char* parola) // testo comincia con parola?
{
    int i;
    int len=strlen(parola);

    for (i=0;i<len && testo[i]!='\0';i++)
    {
        if(parola[i] != testo[i])
            return 0;
    }

    if (i==len) return 1;

    return 0;
}
{% endhighlight %}

[Ecco](correggi2.c) il codice completo.
<!--Il codice-->

<!--`fwrite` funziona così: considera la memoria a partire dall'indirizzo indicato dal puntatore `data`-->

<!--Innanzitutto proviamo a risolvere questo problema: vogliamo chiedere all'utente alcune informazioni anagrafiche che lo descrivono, e vogliamo quindi salvarle su un file, su disco. Successivamente, vogliamo accedere a quelle stesse informazioni, e stamparle a video.-->



<!--Le informazioni che vogliamo memorizzare in modo permanente su file sono:-->

<!--1. Nome-->
<!--2. Cognome-->
<!--3. Numero di telefono-->

<!--C-->



