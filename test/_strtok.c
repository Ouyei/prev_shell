#include "shell.h"

char *_strchr(const char *s, int c);
size_t _strspn(const char *s1, const char *s2);
size_t _strcspn(const char *s1, const char *s2);

/**
 * _strtok - breaks the string s1 into tokens and null-terminates them.
 * Delimiter-Characters at the beginning and end
 *of str are skipped. On each subsequent call delim may change.
 * @str: string to tokenize
 * @delim: string with the character that delimit srt.
 * Return: the first/next token if possible, a null-pointer otherwise.
 **/
char *_strtok(char *str, const char *delim)
{
	static char *p;

	if (str)
		p = str;
	else if (!p)
		return (0);
	str = p + strspn(p, delim);
	p = str + strcspn(str, delim);
	if (p == str)
		return (p = 0);
	p = *p ? *p = 0, p + 1 : 0;
	return (str);
}
