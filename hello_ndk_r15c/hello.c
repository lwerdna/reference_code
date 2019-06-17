#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>

#include <pthread.h>

int speak(void);

int main(int ac, char **av)
{
	printf("Hello, world!\n");

	speak();
    return 0;
}

