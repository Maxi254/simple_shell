#include "shell.h"

/**
 * get_err - calls the err accding the builtin, syn or permission
 * @dtsh: data struct that contains args
 * @ev: err val
 * Return: error
 */
int get_err(dt_shell *dtsh, int ev)
{
	char *err;

	switch (ev)
	{
	case -1:
		error = error_env(datash);
		break;
	case 126:
		error = error_path_126(datash);
		break;
	case 127:
		error = error_not_found(datash);
		break;
	case 2:
		if (_strcmp("exit", datash->args[0]) == 0)
			error = error_exit_shell(datash);
		else if (_strcmp("cd", datash->args[0]) == 0)
			error = error_get_cd(datash);
		break;
	}

	if (error)
	{
		write(STDERR_FILENO, error, _strlen(error));
		free(error);
	}

	datash->status = eval;
	return (eval);
}
