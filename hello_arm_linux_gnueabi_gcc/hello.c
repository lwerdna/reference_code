#include <stdio.h>

int main(int ac, char **av)
{
	printf("Hello, world!\n");

	for(int i=0; i<ac; i++)
	{
		printf("argv[%d] = \"%s\"\n", i, av[i]);
	}

	return 0;
}
