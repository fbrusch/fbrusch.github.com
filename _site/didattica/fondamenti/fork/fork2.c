#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t pid;

    pid = fork();
    if (pid==0)
        printf ("figlio\n");
    else
        printf ("padre\n");
}
