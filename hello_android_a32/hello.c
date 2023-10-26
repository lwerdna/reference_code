#include <stdio.h>

int MyCustomFunction(void)
{
	return 7;
}

int main(int ac, char **av)
{
	char buf[256];
	sprintf(buf, "Hello, world! Lucky number %d!", MyCustomFunction());
	printf("%s\n", buf);
	return 0;
}
