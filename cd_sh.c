#include "shell.h"

/**
 * cd_sh - changes current dir
 * @dtsh: data relevant
 * Return: 1 on success
 */
int cd_sh(dt_shell *dtsh)
{
	char *dir;
	int home, home2, isddash;

	dir = dtsh->as[1];

	if (dir != NULL)
	{
		home = _stcmp("$HOME", dir);
		home2 = _stcmp("~", dir);
		isddash = _stcmp("--", dir);
	}

	if (dir == NULL || !home || !home2 || !isddash)
	{
		cd_t_hom(dtsh);
		return (1);
	}

	if (_stcmp("-", dir) == 0)
	{
		cd_prev(dtsh);
		return (1);
	}

	if (_stcmp(".", dir) == 0 || _stcmp("..", dir) == 0)
	{
		cd_dt(dtsh);
		return (1);
	}

	cd_to(dtsh);

	return (1);
}
