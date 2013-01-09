#include <stdio.h>
#include <stdlib.h>
#include <strings.h>


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

int main()
{

    FILE* f;
    FILE* dest;
    int len;
    char *testo;
    int i;
    char *sbagliata="bruchi";
    char *corretta="bruti";

    f=fopen("ofrati.txt","r");

    fseek(f,0,SEEK_END);
    len=ftell(f);
    testo=malloc(sizeof(char)*(len+1));
    rewind(f);
    fread(testo,sizeof(char),len,f);
    testo[len]='\0';
    printf("%s",testo);

    dest=fopen("corretto.txt","w");

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

    fclose(f);
    fclose(dest);

}
