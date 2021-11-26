#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * get_array - Generate an array (av) whit the arguments in a line.
 * Return: An array whit each argument (word) in the line.
 */
int main(void)
{
	char *buffer = malloc(1024);
	size_t len = 1024;
	char *token;

	while (1)
	{
		printf("$ ");
		getline(&buffer, &len, stdin);
		printf("buffer getline: %s", buffer);
	}
	token = strtok(buffer, " ");
	while (token)
	{
		printf("buffer strtok: %s\n", token);
		token = strtok(NULL, " ");
	}
	return (0);
}
