#include "shell.h"

/**
 * _stct - joins two strs
 * @d: char ptr the dest of the copied str
 * @s: const char ptr the source of str
 * Return: the dest
 */
char *_stct(char *d, const char *s)
{
	int a;
	int x;

	for (a = 0; d[a] != '\0'; a++)
		;

	for (x = 0; s[x] != '\0'; x++)
	{
		d[a] = s[x];
		a++;
	}

	d[a] = '\0';
	return (d);
}
/**
 * *_stcp - Copies the str ptd to by src.
 * @d: Type char ptr the dest of the copied str
 * @s: Type char ptr the source of str
 * Return: the dest.
 */
char *_stcp(char *d, char *s)
{

	size_t i;

	for (i = 0; s[i] != '\0'; i++)
	{
		d[i] = s[i];
	}
	d[i] = '\0';

	return (d);
}
/**
 * _stcmp - Func that compares 2 strs.
 * @s1: type str compared
 * @s2: type str compared
 * Return: Always 0.
 */
int _stcmp(char *s1, char *s2)
{
	int a;

	for (a = 0; s1[a] == s2[a] && s1[a]; a++)
		;

	if (s1[a] > s2[a])
		return (1);
	if (s1[a] < s2[a])
		return (-1);
	return (0);
}
/**
 * _stchr - finds a char in a str
 * @s: str
 * @c: char
 * Return: the ptr to the first occurrence of the char c.
 */
char *_stchr(char *s, char c)
{
	unsigned int a = 0;

	for (; *(s + a) != '\0'; a++)
		if (*(s + a) == c)
			return (s + a);
	if (*(s + a) == c)
		return (s + a);
	return ('\0');
}
/**
 * _stspn - gets the lens of a prefix substr
 * @s: initial
 * @accept: aacc bytes.
 * Return: the number of aacc bytes.
 */
int _stspn(char *s, char *accept)
{
	int i, x, j;

	for (i = 0; *(s + i) != '\0'; i++)
	{
		j = 1;
		for (x = 0; *(accept + x) != '\0'; x++)
		{
			if (*(s + i) == *(accept + x))
			{
				j = 0;
				break;
			}
		}
		if (j == 1)
			break;
	}
	return (i);
}
