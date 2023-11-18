#include "shell.h"

/**
 * bg_line - assigns the line var for gt_line
 * @lptr: Buffer that store the input str
 * @b: str that is been called to line
 * @a: size of line
 * @s: size of buffer
 */
void bg_line(char **lptr, size_t *a, char *b, size_t s)
{

	if (*lptr == NULL)
	{
		if  (s > BUFSIZE)
			*a = s;

		else
			*a = BUFSIZE;
		*lptr = b;
	}
	else if (*a < s)
	{
		if (s > BUFSIZE)
			*a = s;
		else
			*a = BUFSIZE;
		*lptr = b;
	}
	else
	{
		_stcpy(*lptr, b);
		free(b);
	}
}
/**
 * gt_line - Rd inpt from stm
 * @lptr: buff that stores the ipt
 * @a: size of lineptr
 * @stm: stream to read
 * Return: The num of bytes
 */
ssize_t gt_line(char **lptr, size_t *a, FILE *stm)
{
	int i;
	static ssize_t ipt;
	ssize_t r_val;
	char *b;
	char t = 'z';

	if (ipt == 0)
		fflush(stm);
	else
		return (-1);
	ipt = 0;

	b = malloc(sizeof(char) * BUFSIZE);
	if (b == 0)
		return (-1);
	while (t != '\n')
	{
		i = read(STDIN_FILENO, &t, 1);
		if (i == -1 || (i == 0 && input == 0))
		{
			free(b);
			return (-1);
		}
		if (i == 0 && ipt != 0)
		{
			ipt++;
			break;
		}
		if (ipt >= BUFSIZE)
			b = _realloc(b, ipt, ipt + 1);
		b[ipt] = t;
		ipt++;
	}
	b[ipt] = '\0';
	bg_line(lptr, a, b, ipt);
	r_val = ipt;
	if (i != 0)
		ipt = 0;
	return (r_val);
}
