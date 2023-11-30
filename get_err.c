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
		err = err_env(dtsh);
		break;
	case 126:
		err = err_pt(dtsh);
		break;
	case 127:
		err = err_nt_fd(dtsh);
		break;
	case 2:
		if (_stcmp("exit", dtsh->as[0]) == 0)
			err = err_exit_shell(dtsh);
		else if (_stcmp("cd", dtsh->as[0]) == 0)
			err = err_gt_cd(dtsh);
		break;
	}

	if (err)
	{
		write(STDERR_FILENO, err, _stlen(err));
		free(err);
	}

	dtsh->status = ev;
	return (ev);
}
