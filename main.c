#include "shell.h"

/**
 * free_dt - frees data struct
 *
 * @dtsh: data struct
 * Return: no return
 */
void free_data(dt_shell *dtsh)
{
	unsigned int a;

	for (a = 0; dtsh->_environ[a]; a++)
	{
		free(dtsh->_environ[a]);
	}

	free(dtsh->_environ);
	free(dtsh->pid);
}

/**
 * st_dt - Initialize data struct
 *
 * @dtsh: dt struct
 * @ax: argument vector
 * Return: no return
 */
void st_dt(dt_shell *dtsh, char **ax)
{
	unsigned int a;

	dtsh->av = ax;
	dtsh->inpt = NULL;
	dtsh->as = NULL;
	dtsh->status = 0;
	dtsh->count = 1;

	for (a = 0; env[a]; a++)
		;

	dtsh->_environ = malloc(sizeof(char *) * (a + 1));

	for (a = 0; env[a]; a++)
	{  
		dtsh->_environ[a] = _stdp(env[a]);
	}

	dtsh->_environ[a] = NULL;
	dtsh->pid = au_itoa(getpid());
}

/**
 * main - Entry point
 *
 * @ac: argument count
 * @av: argument vector
 *
 * Return: 0 on success.
 */
int main(int ac, char **av)
{
	dt_shell dtsh;
	(void) ac;

	signal(SIGINT, gt_sig);
	st_dt(&dtsh, av);
	shell_loop(&dtsh);
	free_data(&dtsh);
	if (dtsh.status < 0)
		return (255);
	return (dtsh.status);
}
