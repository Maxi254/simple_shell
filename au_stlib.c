#include "shell.h"

/**
 * gt_lens - finds lens of a num
 * @a: type int num.
 * Return: Lens of a number.
 */
int gt_lens(int a)
{
	unsigned int num1;
	int lens = 1;

	if (a < 0)
	{
		lens++;
		num1 = a * -1;
	}
	else
	{
		num1 = a;
	}
	while (num1 > 9)
	{
		lens++;
		num1 = a / 10;
	}

	return (lens);
}
/**
 * au_itoa - func that converts str
 * @a: int num
 * Return: Str.
 */
char *au_itoa(int a)
{
	unsigned int num1;
	int lens = gt_lens(a);
	char *buffer;

	buffer = malloc(sizeof(char) * (lens + 1));
	if (buffer == 0)
		return (NULL);

	*(buffer + lens) = '\0';

	if (a < 0)
	{
		num1 = a * -1;
		buffer[0] = '-';
	}
	else
	{
		num1 = a;
	}

	lens--;
	do {
		*(buffer + lens) = (num1 % 10) + '0';
		num1 = num1 / 10;
		lens--;
	}
	while (num1 > 0)
		;
	return (buffer);
}

/**
 * _atoi - con a str to an int.
 * @a: input string.
 * Return: integer.
 */
int _atoi(char *a)
{
	unsigned int c = 0, s = 0, o = 0, p = 1, m = 1, i;

	while (*(a + c) != '\0')
	{
		if (s > 0 && (*(a + c) < '0' || *(a + c) > '9'))
			break;

		if (*(a + c) == '-')
			p *= -1;

		if ((*(a + c) >= '0') && (*(a + c) <= '9'))
		{
			if (s > 0)
				m *= 10;
			s++;
		}
		c++;
	}

	for (i = c - s; i < c; i++)
	{
		o = o + ((*(a + i) - 48) * m);
		m /= 10;
	}
	return (o * p);
}
