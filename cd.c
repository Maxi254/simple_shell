#include "shell.h"

/**
 * cd_dt - changes to the parent dir
 *
 * @dtsh: data relevant (environ)
 *
 * Return: no return
 */
void cd_dt(dt_shell *dtsh)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_sttk_pwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _stdp(pwd);
	st_env("OLDPWD", cp_pwd, dtsh);
	dir = dtsh->as[1];
	if (_stcmp(".", dir) == 0)
	{
		st_env("PWD", cp_pwd, dtsh);
		free(cp_pwd);
		return;
	}
	if (_stcmp("/", cp_pwd) == 0)
	{
		free(cp_pwd);
		return;
	}
	cp_sttk_pwd = cp_pwd;
	rev_str(cp_sttk_pwd);
	cp_sttk_pwd = _sttk(cp_sttk_pwd, "/");
	if (cp_sttk_pwd != NULL)
	{
		cp_sttk_pwd = _sttk(NULL, "\0");

		if (cp_sttk_pwd != NULL)
			rev_str(cp_sttk_pwd);
	}
	if (cp_sttk_pwd != NULL)
	{
		chdir(cp_sttk_pwd);
		st_env("PWD", cp_sttk_pwd, dtsh);
	}
	else
	{
		chdir("/");
		st_env("PWD", "/", dtsh);
	}
	dtsh->status = 0;
	free(cp_pwd);
}

/**
 * cd_to - changes to a dir
 * @dtsh: data relevant (directories)
 * Return: no return
 */
void cd_to(dt_shell *dtsh)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_dir;

	getcwd(pwd, sizeof(pwd));

	dir = dtsh->as[1];
	if (chdir(dir) == -1)
	{
		get_err(dtsh, 2);
		return;
	}

	cp_pwd = _stdp(pwd);
	st_env("OLDPWD", cp_pwd, dtsh);

	cp_dir = _stdp(dir);
	st_env("PWD", cp_dir, dtsh);

	free(cp_pwd);
	free(cp_dir);

	dtsh->status = 0;

	chdir(dir);
}

/**
 * cd_prev - changes to the previous dir
 * @dtsh: data relevant (environ)
 * Return: no return
 */
void cd_prev(dt_shell *dtsh)
{
	char pwd[PATH_MAX];
	char *p_pwd, *p_oldpwd, *cp_pwd, *cp_oldpwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _stdp(pwd);

	p_oldpwd = _getenv("OLDPWD", dtsh->_environ);

	if (p_oldpwd == NULL)
		cp_oldpwd = cp_pwd;
	else
		cp_oldpwd = _stdp(p_oldpwd);

	st_env("OLDPWD", cp_pwd, dtsh);

	if (chdir(cp_oldpwd) == -1)
		st_env("PWD", cp_pwd, dtsh);
	else
		st_env("PWD", cp_oldpwd, dtsh);

	p_pwd = _getenv("PWD", dtsh->_environ);

	write(STDOUT_FILENO, p_pwd, _stlen(p_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(cp_pwd);
	if (p_oldpwd)
		free(cp_oldpwd);

	dtsh->status = 0;

	chdir(p_pwd);
}

/**
 * cd_t_hom - changes to home directory
 * @dtsh: data relevant (environ)
 * Return: no return
 */
void cd_t_hom(dt_shell *dtsh)
{
	char *p_pwd, *h;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	p_pwd = _stdp(pwd);

	h = _getenv("HOME", dtsh->_environ);

	if (h == NULL)
	{
		st_env("OLDPWD", p_pwd, dtsh);
		free(p_pwd);
		return;
	}

	if (chdir(h) == -1)
	{
		get_err(dtsh, 2);
		free(p_pwd);
		return;
	}

	st_env("OLDPWD", p_pwd, dtsh);
	st_env("PWD", h, dtsh);
	free(p_pwd);
	dtsh->status = 0;
}
