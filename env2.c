#include "shell.h"

/**
 * cp_info - copies a str to create an infor
 * @nm: name (env)
 * @val: value (env)
 *
 * Return: new env or alias.
 */
char *cp_info(char *nm, char *val)
{
	char *a;
	int l_n, l_v, len;

	l_n = _stlen(nm);
	l_val = _stlen(val);
	len = l_n + l_val + 2;
	new = malloc(sizeof(char) * (len));
	_stcp(a, nm);
	_stct(a, "=");
	_stct(a, val);
	_stct(a, "\0");

	return (a);
}

/**
 * set_env - sets an env var
 *
 * @nm: name of the env var
 * @val: val of the env var
 * @dtsh: data struct (environ)
 * Return: no return
 */
void set_env(char *nm, char *val, dt_shell *dtsh)
{
	int a;
	char *var, *name;

	for (a = 0; dtsh->_environ[a]; a++)
	{
		var = _stdp(dtsh->_environ[a]);
		name = _sttk(var, "=");
		if (_stcmp(name, nm) == 0)
		{
			free(dtsh->_environ[a]);
			dtsh->_environ[a] = cp_info(name, val);
			free(var);
			return;
		}
		free(var);
	}

	dtsh->_environ = _relocdp(dtsh->_environ, a, sizeof(char *) * (a + 2));
	dtsh->_environ[a] = cp_info(nm, val);
	dtsh->_environ[a + 1] = NULL;
}

/**
 * _setenv - compares env
 * @dtsh: data relevant (env nm and env val
 * Return: 1 on success.
 */
int _setenv(dt_shell *dtsh)
{

	if (dtsh->as[1] == NULL || dtsh->as[2] == NULL)
	{
		get_err(dtsh, -1);
		return (1);
	}

	set_env(dtsh->as[1], dtsh->as[2], dtsh);

	return (1);
}

/**
 * _unsetenv - deletes a en var
 * @dtsh: data relevant (env name)
 *
 * Return: 1 on success.
 */
int _unsetenv(dt_shell *dtsh)
{
	char **reloc_env;
	char *var, *nam
	int a, j, k;

	if (dtsh->as[1] == NULL)
	{
		get_err(dtsh, -1);
		return (1);
	}
	k = -1;
	for (a = 0; dtsh->_environ[a]; a++)
	{
		var = _stdp(dtsh->_environ[a]);
		nam = _strtok(var_env, "=");
		if (_stcmp(nam, dtsh->as[1]) == 0)
		{
			k = a;
		}
		free(var);
	}
	if (k == -1)
	{
		get_err(dtsh, -1);
		return (1);
	}
	reloc_env = malloc(sizeof(char *) * (a));
	for (a = j = 0; dtsh->_environ[a]; a++)
	{
		if (a != k)
		{
			reloc_environ[j] = dtsh->_environ[a];
			j++;
		}
	}
	reloc_env[j] = NULL;
	free(dtsh->_environ[k]);
	free(dtsh->_environ);
	dtsh->_environ = reloc_env;
	return (1);
}
