#include "shell.h"
/**
 * _exit_command - This function closes the simple_shell
 * @arg: Pointer with the direction argument.
 * @lineptr: Standard input string.
 * @_exit: Value of exit
 * Return: None
 */
void _exit_command(char **directories, char *lineptr, int _exit)
{
	int exit_status = 0;

	if (!directories[1])
	{
		free(lineptr);
		free(directories);
		exit(_exit);
	}
	exit_status = atoi(arg[1]);

	free(lineptr);
	free(directories);
	exit(exit_status);
}

/**
 *_getenv - function to get all env
 *@env: enviroment
 *Return: 0
 */

void _getenv(char **env)
{
	size_t run = 0;

	while (env[run])
	{
		write(STDOUT_FILENO, env[run], _strlen(env[run]));
		write(STDOUT_FILENO, "\n", 1);
		run++;
	}
}
