#include "shell.h"

/**
 * rev_str - reverses a str.
 * @a: input string.
 * Return: no return.
 */
void rev_str(char *a)
{
	int count = 0, i, s;
	char *str, t;

	while (count >= 0)
	{
		if (a[count] == '\0')
			break;
		count++;
	}
	str = a;

	for (i = 0; i < (count - 1); i++)
	{
		for (s = i + 1; s > 0; s--)
		{
			t = *(str + s);
			*(str + s) = *(str + (s - 1));
			*(str + (s - 1)) = t;
		}
	}
}
