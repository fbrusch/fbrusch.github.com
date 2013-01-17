#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("prima di fork()\n");
    fork();
    printf("dopo fork()\n");
}
