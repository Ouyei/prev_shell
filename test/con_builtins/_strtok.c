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
