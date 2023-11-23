#include "shell.h"

/**
 * stct_cd - func that joins the message for cd err
 * @dtsh: data relevant
 * @msg: message to print
 * @err: output message
 * @ver_s: counter lines
 * Return: error message
 */
char *stct_cd(dt_shell *dtsh, char *msg, char *err, char *ver_s)
{
	char *ill_fg;

	_stcp(err, dtsh->av[0]);
	_stct(err, ": ");
	_stct(err, ver_s);
	_stct(err, ": ");
	_stct(err, dtsh->as[0]);
	_stct(err, msg);
	if (dtsh->as[1][0] == '-')
	{
		ill_fg = malloc(3);
		ill_fg[0] = '-';
		ill_fg[1] = dtsh->as[1][1];
		ill_fg[2] = '\0';
		_stct(err, ill_fg);
		free(ill_fg);
	}
	else
	{
		_stct(err, dtsh->as[1]);
	}

	_stct(err, "\n");
	_stct(err, "\0");
	return (err);
}

/**
 * err_gt_cd - error message for cd command in get_cd
 * @dtsh: data relevant (directory)
 * Return: Error message
 */
char *err_gt_cd(dt_shell *dtsh)
{
	int lens, len_id;
	char *err, *ver_str, *msg;

	ver_str = au_itoa(dtsh->count);
	if (dtsh->as[1][0] == '-')
	{
		msg = ": Illegal option ";
		len_id = 2;
	}
	else
	{
		msg = ": can't cd to ";
		len_id = _stlen(dtsh->as[1]);
	}

	lens = _stlen(dtsh->av[0]) + _stlen(dtsh->as[0]);
	lens += _stlen(ver_str) + _stlen(msg) + len_id + 5;
	err = malloc(sizeof(char) * (lens + 1));

	if (err == 0)
	{
		free(ver_str);
		return (NULL);
	}

	err = stct_cd(dtsh, msg, err, ver_str);

	free(ver_str);

	return (err);
}

/**
 * err_nt_fd - absolute error message for command not found
 * @dtsh: data relevancy (counter, arguments)
 * Return: Error message
 */
char *err_nt_fd(dt_shell *dtsh)
{
	int lens;
	char *err;
	char *ver_str;

	ver_str = au_itoa(dtsh->count);
	lens = _stlen(dtsh->av[0]) + _stlen(ver_str);
	lens += _stlen(dtsh->as[0]) + 16;
	err = malloc(sizeof(char) * (lens + 1));
	if (err == 0)
	{
		free(err);
		free(ver_str);
		return (NULL);
	}
	_stcp(err, dtsh->av[0]);
	_stct(err, ": ");
	_stct(err, ver_str);
	_stct(err, ": ");
	_stct(err, dtsh->as[0]);
	_stct(err, ": not found\n");
	_stct(err, "\0");
	free(ver_str);
	return (err);
}

/**
 * err_exit_shell - generic error message for exit in get_exit
 * @dtsh: data relevant (counter, arguments)
 *
 * Return: Error message
 */
char *err_exit_shell(dt_shell *dtsh)
{
	int lens;
	char *err;
	char *ver_str;

	ver_str = au_itoa(dtsh->count);
	lens = _stlen(dtsh->av[0]) + _stlen(ver_str);
	lens += _stlen(dtsh->as[0]) + _stlen(dtsh->as[1]) + 23;
	err = malloc(sizeof(char) * (lens + 1));
	if (err == 0)
	{
		free(ver_str);
		return (NULL);
	}
	_stcp(err, dtsh->av[0]);
	_stct(err, ": ");
	_stct(err, ver_str);
	_stct(err, ": ");
	_stct(err, dtsh->as[0]);
	_stct(err, ": Illegal number: ");
	_stct(err, dtsh->as[1]);
	_stct(err, "\n\0");
	free(ver_str);

	return (err);
}
