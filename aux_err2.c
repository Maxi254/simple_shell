#include "shell.h"

/**
 * err_env - error message for env in get_env.
 * @dtsh: data relevant (counter, arguments)
 * Return: error message.
 */
char *err_env(dt_shell *dtsh)
{
	int lens;
	char *err;
	char *ver_str;
	char *msg;

	ver_str = au_itoa(dtsh->count);
	msg = ": Unable to add/remove from environment\n";
	lens = _stlen(dtsh->av[0]) + _stlen(ver_str);
	lens += _stlen(dtsh->as[0]) + _stlen(msg) + 4;
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
	_stct(err, msg);
	_stct(err, "\0");
	free(ver_str);

	return (err);
}
/**
 * err_pt - error message for path and failure denied permission.
 * @dtsh: data relevant (count, arguments).
 *
 * Return: The error string.
 */
char *err_pt(dt_shell *dtsh)
{
	int lens;
	char *ver_str;
	char *err;

	ver_str = au_itoa(dtsh->count);
	lens = _stlen(dtsh->av[0]) + _stlen(ver_str);
	lens += _stlen(dtsh->as[0]) + 24;
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
	_stct(err, ": Permission denied\n");
	_stct(err, "\0");
	free(ver_str);
	return (err);
}
