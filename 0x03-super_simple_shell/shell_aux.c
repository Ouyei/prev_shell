#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	char *line;
	size_t len = 0;
	int printchars = 0;

	while(1)
	{
		printf("#cisfun$ ");
		printchars = getline(&line, &len, stdin);
		if (printchars == -1)
		{
			printf("%d\n", printchars);
			break;
		}
		if (printchars == 0)
			printf("%s", line);
		else if (*line != '\n')
		{
			printf("%s", line);
		}
	}
	free(line);
	return (0);
}
