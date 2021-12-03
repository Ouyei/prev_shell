#include "shell.h"
/**
 * main - main arguments functions
 * @ac:count of argumnents
 * @av: arguments
 * @env: environment
 * Return: _exit = 0.
 */
int main(int ac, char **av, char **env)
{
	char *line = NULL;
	char **args = NULL;
	int pathValue = 0;
	int stat = 0, n = 0;
	(void)ac;

	while (1)
	{
		line = _getline_command();/** reads user input*/
		if (line)
		{
			pathValue++;
			args = _get_token(line);/** tokenizes user input*/
			if (!args)
			{
				free(line);
				continue;
			}
			if ((!_strcmp(args[0], "exit")) && args[1] == NULL)/** user wrote "exit"*/
				_exit_command(args, line, stat);
			if (!_strcmp(args[0], "env"))/**checks if user wrote env"*/
				_getenv(env);
			else
			{
				n = _values_path(&args[0], env);/** tokenizes PATH*/
				stat = _fork_fun(args, av, env, line, pathValue, n);
				if (n == 0)
					free(args[0]);
			}
			free(args);
		}
		else
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			exit(stat);
		}
		free(line);
	}
	return (stat);
}
