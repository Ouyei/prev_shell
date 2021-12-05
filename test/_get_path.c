#include "shell.h"
/**
 * _get_path - Get variable PATH.
 * @env: Local enviroment.
 * Return: value of PATH.
 */

char *_get_path(char **env)
{
	char *path = NULL;
	size_t var, index = 0, count = 5;

	for (index = 0; _strncmp(env[index], "PATH=", 5); index++)
		;
	if (env[index] == NULL)
		return (NULL);

	for (count = 5; env[index][var]; var++, count++)
		;
	path = malloc(sizeof(char) * (count + 1));

	if (path == NULL)
		return (NULL);

	for (var = 5, count = 0; env[index][var]; var++, count++)
		path[count] = env[index][var];

	path[count] = '\0';
	return (path);
}
