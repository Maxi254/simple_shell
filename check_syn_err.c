#include "shell.h"

/**
 * rep_char - counts the reps of a char
 * @ipt: input str
 * @i: index
 * Return: repetitions
 */
int rep_char(char *ipt, int i)
{
	if (*(ipt - 1) == *ipt)
		return (rep_char(ipt - 1, i + 1));

	return (i);
}

/**
 * err_sep_op - finds syn err
 *
 * @ipt: ipt str
 * @i: index
 * @l: last char read
 * Return: index of error. 0 when there are no
 */
int err_sep_op(char *ipt, int i, char l)
{
	int a;

	a = 0;
	if (*ipt == '\0')
		return (0);

	if (*ipt == ' ' || *ipt == '\t')
		return (err_sep_op(ipt + 1, i + 1, l));

	if (*ipt == ';')
		if (l == '|' || l == '&' || l == ';')
			return (i);

	if (*ipt == '|')
	{
		if (l == ';' || l == '&')
			return (i);

		if (l == '|')
		{
			a = rep_char(ipt, 0);
			if (a == 0 || a > 1)
				return (i);
		}
	}

	if (*ipt == '&')
	{
		if (l == ';' || l == '|')
			return (i);

		if (l == '&')
		{
			a = rep_char(ipt, 0);
			if (a == 0 || a > 1)
				return (i);
		}
	}

	return (err_sep_op(ipt + 1, i + 1, *ipt));
}

/**
 * ft_char - gets first char
 * @ipt: imput from the user
 * @i: index
 * Return: 0 for success, 1 for error
 */
int ft_char(char *ipt, int *i)
{

	for (*i = 0; ipt[*i]; *i += 1)
	{
		if (ipt[*i] == ' ' || ipt[*i] == '\t')
			continue;

		if (ipt[*i] == ';' || ipt[*i] == '|' || ipt[*i] == '&')
			return (-1);

		break;
	}

	return (0);
}

/**
 * pt_syn_err - ptss when a syn err is found
 * @dtsh: data structure
 * @ipt: ipt str
 * @i: index of the err
 * @b: to control msg error
 * Return: no return
 */
void pt_syn_err(dt_shell *dtsh, char *ipt, int i, int b)
{
	char *m, *m2, *m3, *err, *c;
	int lens;

	if (ipt[i] == ';')
	{
		if (b == 0)
			m = (ipt[i + 1] == ';' ? ";;" : ";");
		else
			m = (ipt[i - 1] == ';' ? ";;" : ";");
	}

	if (ipt[i] == '|')
		m = (ipt[i + 1] == '|' ? "||" : "|");

	if (ipt[i] == '&')
		m = (ipt[i + 1] == '&' ? "&&" : "&");

	m2 = ": Syntax error: \"";
	m3 = "\" unexpected\n";
	c = aux_itoa(datash->counter);
	lens = _stlen(datash->av[0]) + _stlen(counter);
	length += _strlen(msg) + _strlen(msg2) + _strlen(msg3) + 2;

	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(counter);
		return;
	}
	_strcpy(error, datash->av[0]);
	_strcat(error, ": ");
	_strcat(error, counter);
	_strcat(error, msg2);
	_strcat(error, msg);
	_strcat(error, msg3);
	_strcat(error, "\0");

	write(STDERR_FILENO, error, length);
	free(error);
	free(counter);
}

/**
 * check_syntax_error - intermediate function to
 * find and print a syntax error
 *
 * @datash: data structure
 * @input: input string
 * Return: 1 if there is an error. 0 in other case
 */
int check_syntax_error(data_shell *datash, char *input)
{
	int begin = 0;
	int f_char = 0;
	int i = 0;

	f_char = first_char(input, &begin);
	if (f_char == -1)
	{
		print_syntax_error(datash, input, begin, 0);
		return (1);
	}

	i = error_sep_op(input + begin, 0, *(input + begin));
	if (i != 0)
	{
		print_syntax_error(datash, input, begin + i, 1);
		return (1);
	}

	return (0);
}
