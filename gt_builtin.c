#include "shell.h"

/**
 * gt_builtin - gets in builtin commands
 * @cmd: command
 * Return: func ptrr of the builtin cmd
 */
int (*gt_builtin(char *cmd))(dt_shell *dtsh)
{
	builtin_t builtin[] = {
		{ "env", _env },
		{ "exit", exit_shell },
		{ "setenv", _setenv },
		{ "unsetenv", _unsetenv },
		{ "cd", cd_sh },
		{ "help", get_help },
		{ NULL, NULL }
	};
	int a;

	for (a = 0; builtin[a].name; a++)
	{
		if (_stcmp(builtin[a].name, cmd) == 0)
			break;
	}

	return (builtin[a].f);
}
