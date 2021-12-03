#include "shell.h"
/**
 * main - Main arguments functions
 * @ac: Count of argumnents
 * @av: Arguments
 * @env: Environment
 * Return: _exit = 0.
 */
int main(int ac, char **av, char **env)
{
	int pathValue = 0;
	int status = 0, interactive = 0;
	char *line = NULL;
	/* pointer to array of string with the directories. i.e. "usr/bin" */
	char **directories = NULL;
	(void)ac;
	/* loop until exit */
	while (1)
	{
		line = _getline_command();/** reads user input*/
		if (line)
		{
			pathValue++;
			directories = _get_token(line);/** tokenizes or parse user input*/
			if (!directories)
			{
				free(line);
				continue;
			}
			if ((!_strcmp(directories[0], "exit")) && directories[1] == NULL)/** user wrote "exit"*/
				_exit_command(directories, line, status);
			if (!_strcmp(directories[0], "env"))/**checks if user wrote env"*/
				_getenv(env);
			else
			{
				interactive = _values_path(&directories[0], env);/** tokenizes PATH*/
				status = _fork_fun(directories, av, env, line, pathValue, interactive);
				if (interactive == 0)
					free(directories[0]);
			}
			free(directories); /*free up memory*/
		}
		else
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);/*ACA EJECUTA????!!!!!*/
			exit(status);
		}
		free(line);
	}
	return (status);
}
