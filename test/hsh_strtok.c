#include "shell.h"
/**
 * _strtok - Breaks the string s1 into tokens and null-terminates them.
 * Delimiter-Characters at the beginning and end
 *of str are skipped. On each subsequent call delim may change.
 * @str: String to tokenize.
 * @delim: String with the character that delimit srt.
 * Return: First/next token if possible, a null-pointer otherwise.
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
