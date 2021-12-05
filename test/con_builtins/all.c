#include "shell.h"
/**
 * _exit_command - this function closes the simple_shell when
 * @arg: pointer with the direction argument.
 * @lineptr: standar input string
 * @_exit: value of exit
 */
void _exit_command(char **arg, char *lineptr, int _exit)
{
	int exit_status = 0;

	if (!arg[1])
	{
		free(lineptr);
		free(arg);
		exit(_exit);
	}
	exit_status = atoi(arg[1]);

	free(lineptr);
	free(arg);
	exit(exit_status);
}

/**
 * _getenv - prints the env to stdout
 * @env: enviroment
 *
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
#include "shell.h"
/**
* on Declarations for builtin shell commands:
*/
int lsh_cd(char **args);
int lsh_help(char **args);
int lsh_exit(char **args);

/*
 * List of builtin commands, followed by their corresponding functions.
 */
char *builtin_str[] = {"cd", "help", "exit"};

int (*builtin_func[]) (char **) = {&lsh_cd, &lsh_help, &lsh_exit};

int lsh_num_builtins(void)
{
	return (sizeof(builtin_str) / sizeof(char *));
}

/*
 * Builtin function implementations.
*/

/**
   @brief Bultin command: change directory.
   @param args List of args.  args[0] is "cd".  args[1] is the directory.
   @return Always returns 1, to continue executing.
 */
int lsh_cd(char **args)
{
	if (args[1] == NULL)
	{
		fprintf(stderr, "lsh: expected argument to \"cd\"\n");
	}
	else
	{
		if (chdir(args[1]) != 0)
		{
			perror("lsh");
		}
	}
	return (1);
}

/**
   @brief Builtin command: print help.
   @param args List of args.  Not examined.
   @return Always returns 1, to continue executing.
 */
int lsh_help(char **args)
{
  int i;
  printf("Oscar Bedat and Andres Henderson\n");
  printf("If you need help, call 1-800-help\n");
  (void)args;
  for (i = 0; i < lsh_num_builtins(); i++)
  {
	  printf("  %s\n", builtin_str[i]);
  }

  printf("Use the man command for information on other programs.\n");
  return (1);
}

/**
   @brief Builtin command: exit.
   @param args List of args.  Not examined.
   @return Always returns 0, to terminate execution.
 */
int lsh_exit(char **args)
{
	(void)args;
	printf("should exit\n");
	free(args);
	return (200);
}



/** ion that create a fork.
 *@arg: Command and values path.
 *@av: Has the name of our program.
 *@env: Environment
 *@lineptr: Command line for the user.
 *@np: ID of proces.
 *@c: Checker add new test
 *Return: 0 success
 */

int _fork_fun(char **arg, char **av, char **env, char *lineptr, int np, int c)
{

	pid_t child;
	int status, i = 0;
	char *format = "%s: %d: %s: not found\n";

	if (arg[0] == NULL)
		return (1);
	for (i = 0; i < lsh_num_builtins(); i++)
	{
		if (_strcmp(arg[0], builtin_str[i]) == 0)
				return (builtin_func[i](arg));
	}
	child = fork();
	if (child == 0)
	{
		if (execve(arg[0], arg, env) == -1)
		{
			fprintf(stderr, format, av[0], np, arg[0]);
			if (!c)
				free(arg[0]);
			free(arg);
			free(lineptr);
			exit(errno);
		}
	}
	else
	{
		wait(&status);
		return (status);
	}
	return (0);
}
#include "shell.h"
/**
 * _getline_command - Print "#cisfun$ " and wait for the user type something.
 * Return: The line of string input for user.
 */

char *_getline_command(void)
{
	char *lineptr = NULL;
	size_t charter_user = 0;

	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "$ ", 2);

	if (getline(&lineptr, &charter_user, stdin) == -1)
	{
		free(lineptr);
		return (NULL);
	}

	return (lineptr);
}
#include "shell.h"
/**
 * _get_path - get variable PATH.
 * @env: enviromente local
 * Return: value of PATH.
 */

char *_get_path(char **env)
{
	size_t index = 0, var = 0, count = 5;
	char *path = NULL;

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
	int pathValue = 0, status = 0, interactive = 0;
	char *line = NULL; /** a pointer to the input*/
	/* pointer to array of string with the directories. i.e. "usr/bin" */
	char **commands = NULL; /**these are the tokenized commands*/
	(void)ac;
	/* loop until exit */
	while (1)
	{
		line = _getline_command();/** reads user input*/
		if (line)
		{
			pathValue++;
			commands = tokenize(line);/** tokenizes or parse user input*/
			if (!commands)
			{
				free(line);
				continue;
			} /**user inputed "exit"*/
			if (!_strcmp(commands[0], "env"))/**checks if user wrote env"*/
			{
				free(line);
				_getenv(env);
			}
			else
			{
				interactive = _values_path(&commands[0], env);/** tokenizes PATH*/
				status = _fork_fun(commands, av, env, line, pathValue, interactive);
					if (status == 200)
					{
						free(line);
						return (0);
					}
				if (interactive == 0)
					free(commands[0]);
			}
			free(commands); /*free up memory*/
		}
		else
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);/** Writes to standard output*/
			exit(status);
		}
		free(line);
	}
	return (status);
}
#include "shell.h"

/**
 * _strcat -  Concatenates two strings
 *
 * @dest: Destination string
 *
 * @src: Origin string
 * Return: Always 0
 */



char *_strcat(char *dest, char *src)
{
	int i, j = 0;

	for (i = 0; dest[i] != '\0'; i++)
	{
	}
	for (j = 0; src[j] != '\0'; j++)
	{
		dest[i] = src[j];
		i++;

	}
	dest[i] = '\0';
return (dest);
}



/**
 * _strcmp - Compares two strings
 *
 * @s1: a string
 * @s2: Another string
 *
 * Return: multiple returns
 *
 */

int _strcmp(char *s1, char *s2)
{
	int i = 0;
	int val;

	while (s1[i] != 0 && s2[i] != 0 && s1[i] == s2[i])
		i++;
val = s1[i] - s2[i];
return (val);

}

/**
 * _strlen - gets the size of a string
 * @s: the string to measure
 * Return: the length of the string
 */

int _strlen(char *s)
{
	int i;

	for (i = 0; s[i] != 0; i++)
		;

	return (i);
}

/**
 *_strncmp -  function that compares two strings.
 *@s1: string one
 *@s2: string two
 *@n: number of characters
 * Return: diference
 */

size_t _strncmp(char *s1, char *s2, size_t n)
{
	size_t i, j;

	for (j = 0; s1[j] != '\0' && j < n; j++)
	{
		i = s1[j] - s2[j];

		if (i != 0)
		{
			return (i);
		}
	}
	return (0);
}

/**
 * _strcpy - copies the string pointed to by src into dest
 * @dest: destination of the copy
 * @src: source of the copy
 *
 * Return: char pointer to dest
 */

char *_strcpy(char *dest, char *src)
{
	int i = 0;

	for (i = 0; src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}
	dest[i + 1] = 0;
	return (dest);
}

















#include "shell.h"
/**
 * tokenize - tokenizes a stirng
 * @lineptr: what the user inputed
 * Return: a ptr to arr of ptrs
 */

char **tokenize(char *lineptr)
{
	char **user_command = NULL;
	char *token = NULL;
	size_t i = 0;
	int size = 0;

	if (lineptr == NULL)
		return (NULL);

	for (i = 0; lineptr[i]; i++)
	{
		if (lineptr[i] == ' ')
			size++;
	}
	if ((size + 1) == _strlen(lineptr))
		return (NULL);
	user_command = malloc(sizeof(char *) * (size + 2));
	if (user_command == NULL)
		return (NULL);

	token = strtok(lineptr, " \n\t\r");
	for (i = 0; token != NULL; i++)
	{
		user_command[i] = token;
		token = strtok(NULL, " \n\t\r");
	}
	user_command[i] = NULL;
	return (user_command);
}
#include "shell.h"
/**
 * _values_path - Separate the path in new strings.
 * @arg: Command input of user.
 * @env: Enviroment.
 * Return: Pointer to strings.
 */
int _values_path(char **arg, char **env)
{
	char *token = NULL, *path_rela = NULL, *path_absol = NULL;
	size_t value_path, len;
	struct stat stat_lineptr;

	if (stat(*arg, &stat_lineptr) == 0)
		return (-1);
	path_rela = _get_path(env);/** gets the content of "PATH="*/
	if (!path_rela)
		return (-1);
	token = strtok(path_rela, ":"); /**tokenizes the content of "PATH="*/
	len = _strlen(*arg); /**gets length of arg*/
	while (token)
	{
		value_path = _strlen(token);
		path_absol = malloc(sizeof(char) * (value_path + len + 2));
		if (!path_absol)
		{
			free(path_rela);
			return (-1);
		}
		path_absol = _strcpy(path_absol, token);
		_strcat(path_absol, "/");
		_strcat(path_absol, *arg);

		if (stat(path_absol, &stat_lineptr) == 0)
		{
			*arg = path_absol;
			free(path_rela);
			return (0);
		}
		free(path_absol);
		token = strtok(NULL, ":");
	}
	token = '\0';
	free(path_rela);
	return (-1);
}
#include "shell.h"
/**
 * _strtok - Tokenizes a string
 * @string: the string to be tokenized and stored in array
 * Return: a pointer to an array of pointers to char
 */
char *_strtok(char *string, const char *delim)
{
	int bufsize = 1024, ctr = 0;
	char **token_array; /**to store all the tokens*/
	char *token; /** to store each token*/
	/** allocate mem for the array, and check if it worked*/
	token_array = malloc(bufsize * sizeof(char *));
	if (!token_array)
	{ /**per man exit, you call EXIT_FAILURE*/
		exit(EXIT_FAILURE);
	}

	token = strtok(string, delim);/**the assign the first token*/
	/**In ASCII: " " = 32; \t = 9; \r = 13; \n = 10; \a = 7;*/
	while (token != NULL) /** the walk the string and store tokens in array*/
	{
		token_array[ctr++] = token;
		token = strtok(NULL, delim);
	}
	token_array[ctr] = 0;/** add sentinel value to know when array ends*/
	return (*token_array);
  /**
   * One issue could be that you have to duplicate the string, because strtok
   * works on the provided string, and if it can't modify it, it will dump.
   */
}
#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>


int lsh_cd(char **args);
int lsh_help(char **args);
extern char **environ;
int lsh_exit(char **args);
int _strcmp(char *s1, char *s2);
size_t _strncmp(char *s1, char *s2, size_t n);
int _strlen(char *s);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);
int _putchar(char c);

char *_get_path(char **env);
int _values_path(char **arg, char **env);
char *_getline_command(void);
void _getenv(char **env);
char **tokenize(char *lineptr);
void _exit_command(char **args, char *lineptr, int _exit);
int _fork_fun(char **arg, char **av, char **env,
char *lineptr, int np, int c);
char *_strtok(char *str, const char *delim);


#endif /* SHELL_H */
