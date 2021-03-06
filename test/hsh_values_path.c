#include "shell.h"
/**
 * _values_path - Separate the path in new strings.
 * @arg: Command input of user.
 * @env: Enviroment.
 * Return: Pointer to strings.
 */

int _values_path(char **directories, char **env)
{
	char *token = NULL, *path_rela = NULL, *path_absol = NULL;
	size_t value_path, command;
	struct stat stat_lineptr;

	if (stat(*directories, &stat_lineptr) == 0)
		return (-1);
	path_rela = _get_path(env);
	if (!path_rela)
		return (-1);
	/** here we tokenize the path*/
	token = _strtok(path_rela, ":");
	command = strlen(*directories);
	while (token)
	{
		value_path = strlen(token);
		path_absol = malloc(sizeof(char) * (value_path + command + 2));
		if (!path_absol)
		{
			free(path_rela);
			return (-1);
		}
		path_absol = _strcpy(path_absol, token);
		strcat(path_absol, "/");
		strcat(path_absol, *directories);
		/** the [0] is "PATH"*/
		if (stat(path_absol, &stat_lineptr) == 0)
		{
			*directories = path_absol;
			free(path_rela);
			return (0);
		}
		free(path_absol);
		token = _strtok(NULL, ":");
	}
	free(path_rela);
	return (-1);
}
