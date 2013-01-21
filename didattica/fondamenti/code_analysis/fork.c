#include <stdio.h>
#include <unistd.h>


int main()
{
	printf("a\n");
	fork();
	printf("b\n");
	if (fork()==0)
		printf("d\n");
	else
		printf("e\n");
}