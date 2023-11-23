#include "shell.h"

/**
 * cp_env_nm - compares environment vars nams
 * @n_env: name of the env var
 * @nm: name passed
 *
 * Return: 0 if are not equal. Another value if they are.
 */
int cp_env_nm(const char *n_env, const char *nm)
{
	int a;

	for (a = 0; n_env[a] != '='; a++)
	{
		if (n_env[a] != nm[a])
		{
			return (0);
		}
	}

	return (a + 1);
}

/**
 * _getenv - get an env var
 * @nm: name of the env var
 * @_env: environment var
 *
 * Return: value of the environment variable if is found.
 * In other case, returns NULL.
 */
char *_getenv(const char *nm, char **_env)
{
	char *pt_env;
	int a, m;

	
	pt_env = NULL;
	m = 0;
	
	
  for (a = 0; _env[a]; a++)
	{
		
		m = cp_env_nm(_env[a], nm);
		if (m)
		{
			pt_env = _env[a];
			break;
		}
	}

	return (pt_env + m);
}

/**
 * _env - prints the env var
 *
 * @dtsh: dt relevant.
 * Return: 1 on success.
 */
int _env(dt_shell *dtsh)
{
	int a, j;

	for (a = 0; dtsh->_environ[a]; a++)
	{

		for (j = 0; dtsh->_environ[a][j]; j++)
			;

		write(STDOUT_FILENO, dtsh->_environ[a], j);
		write(STDOUT_FILENO, "\n", 1);
	}
	dtsh->status = 0;

	return (1);
}
