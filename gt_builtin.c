#include "shell.h"

/**
 * gt_builtin - gets in builtin commands
 * @cmd: command
 * Return: func ptrr of the builtin cmd
 */
int (*gt_builtin(char *cmd))(dt_shell *)
{
	builtin_t builtin[] = {
		{ "env", env },
		{ "exit", exit_shell },
		{ "setenv", setenv },
		{ "unsetenv", unsetenv },
		{ "cd", cd_shell },
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
