#include <stdio.h>
#include <stdlib.h>
/**
 * main- Program that prints \"$ \", wait for the user to enter a command,
 * prints it on the next line.
 * Return: Always 0.
 */
int main(void)
{
	char *buffer = malloc(1024);
	size_t len = 1024;

	while (1)
	{
		printf("$ ");
		getline(&buffer, &len, stdin);
		prinf("%s", buffer);
	}
	return (0);
}
