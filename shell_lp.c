#include "shell.h"

/**
 * wt_comm - deletes comms from the ipt
 *
 * @in: ipt str
 * Return: input without comments
 */
char *wt_comm(char *in)
{
	int i, ut;

	ut = 0;
	for (i = 0; in[i]; i++)
	{
		if (in[i] == '#')
		{
			if (i == 0)
			{
				free(in);
				return (NULL);
			}

			if (in[i - 1] == ' ' || in[i - 1] == '\t' || in[i - 1] == ';')
				u_t = i;
		}
	}

	if (u_t != 0)
	{
		in = reloc(in, i, ut + 1);
		in[ut] = '\0';
	}

	return (in);
}

/**
 * shell_lp - Loop of shell
 * @dtsh: dt relevant (av, ipt, args)
 *
 * Return: no return.
 */
void shell_lp(dt_shell *dtsh)
{
	int lp, i_eof;
	char *ipt;

	lp = 1;
	while (lp == 1)
	{
		write(STDIN_FILENO, "^-^ ", 4);
		ipt = read_line(&i_eof);
		if (i_eof != -1)
		{
			ipt = wt_comm(ipt);
			if (ipt == NULL)
				continue;

			if (check_syn_err(dtsh, ipt) == 1)
			{
				dtsh->status = 2;
				free(ipt);
				continue;
			}
			ipt = rep_var(ipt, dtsh);
			lp = spt_cmds(dtsh, ipt);
			dtsh->count += 1;
			free(ipt);
		}
		else
		{
			lp = 0;
			free(ipt);
		}
	}
}
