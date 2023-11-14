#include "shell.h"

/**
 * _stdp - makes anothe str in the hp memo.
 * @a: Type char ptr str
 * Return: duplicated str
 */
char *_stdp(const char *a)
{
	char *n;
	size_t lens;

	lens = _strlen(a);
	n = malloc(sizeof(char) * (lens + 1));
	if (n == NULL)
		return (NULL);
	_memcp(n, a, lens + 1);
	return (n);
}

/**
 * _stlen - Brings the length of a str.
 * @a: Type char ptr
 * Return: Always 0.
 */
int _stlen(const char *a)
{
	int lens;

	for (lens = 0; a[lens] != 0; lens++)
	{
	}
	return (lens);
}

/**
 * cm_char - compare chars of strs
 * @str: input str
 * @dem: delimiter.
 *
 * Return: 1 if are equals, 0 if not.
 */
int cm_char(char str[], const char *dem)
{
	unsigned int i, a, k;

	for (i = 0, k = 0; str[i]; i++)
	{
		for (a = 0; dem[a]; a++)
		{
			if (str[i] == dem[a])
			{
				k++;
				break;
			}
		}
	}
	if (i == k)
		return (1);
	return (0);
}

/**
 * _sttok - splits a str by some delimiter.
 * @str: input str.
 * @dem: delimiter.
 *
 * Return: string splited.
 */
char *_sttok(char str[], const char *dem)
{
	static char *spd, *str_end;
	char *str_star;
	unsigned int i, b;

	if (str != NULL)
	{
		if (cm_char(str, dem))
			return (NULL);
		spd = str
		i = _stlen(str);
		str_end = &str[i]; /*Stost address*/
	}
	str_star = spd;
	if (str_star == str_end) 
		return (NULL);

	for (b = 0; *spd; spd++)
	{
		/*we trying to break loop here*/
		if (spd != str_star)
			if (*spd && *(spd - 1) == '\0')
				break;
		/*lets replace the delimiter here*/
		for (i = 0; dem[i]; i++)
		{
			if (*spd == dem[i])
			{
				*spd = '\0';
				if (spd == str_star)
					str_star++;
				break;
			}
		}
		if (b == 0 && *spd)
			b = 1;
	}
	if (b == 0) /*S == Dm*/
		return (NULL);
	return (str_star);
}

/**
 * _isdigit - makes sure a digit is passed to a number 
 * @s: input str
 * Return: 1 if string is a number. 0 in other case.
 */
int _isdigit(const char *s)
{
	unsigned int i;

	for (i = 0; s[i]; i++)
	{
		if (s[i] < 48 || s[i] > 57)
			return (0);
	}
	return (1);
}
