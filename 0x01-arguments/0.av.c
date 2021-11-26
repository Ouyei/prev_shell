#include <stdio.h>

/**
 * main - Function that prints all the arguments given, without using ac.
 * @ac: Number of arguments given.
 * @av: Pointer with adrress to pointer to arguments given.
 * Return: Always 0.
 */
int main(int ac, char **av)
{
	int i = 0;

	while (av[i])
	{
		printf("%s ", av[i]);
		i++;
	}
	printf("\n");
	return (0);
}
