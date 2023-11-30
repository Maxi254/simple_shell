#include "shell.h"

/**
 * get_help - func that retrieves help messages according builtin
 * @datash: data struct (args and input)
 * Return: Return 0
*/
int gt_help(dt_shell *dtsh)
{

	if (dtsh->as[1] == 0)
		aux_help_general();
	else if (_stcmp(dtsh->as[1], "setenv") == 0)
		aux_help_setenv();
	else if (_stcmp(dtsh->as[1], "env") == 0)
		aux_help_env();
	else if (_stcmp(dtsh->as[1], "unsetenv") == 0)
		aux_help_unsetenv();
	else if (_strcmp(dtsh->as[1], "help") == 0)
		aux_help();
	else if (_stcmp(dtsh->as[1], "exit") == 0)
		aux_help_exit();
	else if (_strcmp(dtsh->as[1], "cd") == 0)
		aux_help_cd();
	else if (_stcmp(dtsh->as[1], "alias") == 0)
		aux_help_alias();
	else
		write(STDERR_FILENO, dtsh->as[0],
		      _stlen(dtsh->as[0]));

	dtsh->status = 0;
	return (1);
}
