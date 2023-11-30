#include "shell.h"

/**
 * exit_sh - exits the shelll
 * @dtsh: data relevant (status and args)
 * Return: 0 on success.
 */
int exit_sh(dt_shell *dtsh)
{
	unsigned int us;
	int is_digit;
	int st_len;
	int big_num;

	if (dtsh->as[1] != NULL)
	{
		us = _atoi(dtsh->as[1]);
		is_digit = _isdigit(dtsh->as[1]);
		st_len = _stlen(dtsh->as[1]);
		big_num = us > (unsigned int)INT_MAX;
		if (!is_digit || st_len > 10 || big_num)
		{
			get_err(dtsh, 2);
			dtsh->status = 2;
			return (1);
		}
		dtsh->status = (us % 256);
	}
	return (0);
}
