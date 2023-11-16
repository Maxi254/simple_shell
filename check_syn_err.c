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
	c = aux_itoa(dtsh->counter);
	lens = _stlen(dtsh->av[0]) + _stlen(c);
	lens += _stlen(m) + _stlen(m2) + _stlen(m3) + 2;

	err = malloc(sizeof(char) * (lens + 1));
	if (err == 0)
	{
		free(c);
		return;
	}
	_stcpy(err, dtsh->av[0]);
	_stct(err, ": ");
	_stct(err, c);
	_stct(err, m2);
	_stct(err, m);
	_stct(err, m3);
	_strct(err, "\0");

	write(STDERR_FILENO, err, lens);
	free(err);
	free(c);
}

/**
 * check_syn_err - fuction to find intermediatires
 * @dtsh: data struct
 * @ipt: input str
 * Return: 1 if there is an err. 0 in other case
 */
int check_syn_err(dt_shell *dtsh, char *ipt)
{
	int b = 0;
	int fchar = 0;
	int a = 0;

	fchar = first_char(ipt, &b);
	if (fchar == -1)
	{
		pt_syn_err(dtsh, ipt, b, 0);
		return (1);
	}

	i = err_sep_op(ipt + b, 0, *(ipt + b));
	if (a != 0)
	{
		pt_syn_err(dtsh, ipt, b + a, 1);
		return (1);
	}

	return (0);
}
