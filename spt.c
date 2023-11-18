#include "shell.h"

/**
 * sp_char - sps | and & for non-printed chars
 * @ipt: input str
 * @b: type of swap
 * Return: swapped str
 */
char *sp_char(char *ipt, int b)
{
	int a;

	if (b == 0)
	{
		for (a = 0; ipt[a]; a++)
		{
			if (ipt[a] == '|')
			{
				if (ipt[a + 1] != '|')
					ipt[a] = 16;
				else
					a++;
			}

			if (ipt[a] == '&')
			{
				if (ipt[a + 1] != '&')
					ipt[a] = 12;
				else
					a++;
			}
		}
	}
	else
	{
		for (a = 0; ipt[a]; a++)
		{
			ipt[a] = (ipt[a] == 16 ? '|' : ipt[a]);
			ipt[a] = (ipt[a] == 12 ? '&' : ipt[a]);
		}
	}
	return (ipt);
}

/**
 * add_nod - add separators and command lines in the lists
 *
 * @h_s: hd of separator list
 * @h_l: hd of command lines list
 * @ipt: ipt string
 * Return: no return
 */
void add_nod(sepa_list **h_s, line_list **h_l, char *ipt)
{
	int a;
	char *line;

	ipt = sp_char(ipt, 0);

	for (a = 0; ipt[a]; a++)
	{
		if (ipt[a] == ';')
			add_sep_nod_end(h_s, ipt[a]);

		if (ipt[a] == '|' || ipt[a] == '&')
		{
			add_sep_nod_end(h_s, ipt[a]);
			a++;
		}
	}

	line = _sttok(ipt, ";|&");
	do {
		line = sp_char(line, 1);
		add_line_nod_end(h_l, line);
		line = _sttok(NULL, ";|&");
	} while (line != NULL);

}

/**
 * go_nt - go to the next cmd line stored
 * @lt_s: separator list
 * @lt_l: cmd line list
 * @dtsh: data struct
 * Return: no return
 */
void go_nt(sepa_list **lt_s, line_list **lt_l, dt_shell *dtsh)
{
	int lp_sep;
	sepa_list *ls_s;
	line_list *ls_l;

	lp_sep = 1;
	ls_s = *lt_s;
	ls_l = *lt_l;

	while (ls_s != NULL && lp_sep)
	{
		if (dtsh->status == 0)
		{
			if (ls_s->separator == '&' || ls_s->separator == ';')
				lp_sep = 0;
			if (ls_s->separator == '|')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		else
		{
			if (ls_s->separator == '|' || ls_s->separator == ';')
				lp_sep = 0;
			if (ls_s->separator == '&')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		if (ls_s != NULL && !lp_sep)
			ls_s = ls_s->next;
	}

	*lt_s = ls_s;
	*lt_l = ls_l;
}

/**
 * spt_cms - splits cmd lines according to the sepa
 * @dtsh: data struct
 * @ipt: input string
 * Return: 0 to exit, 1 to continue
 */
int spt_cms(dt_shell *dtsh, char *ipt)
{

	sepa_list *h_s, *lt_s;
	line_list *h_l, *lt_l;
	int l;

	h_s = NULL;
	h_l = NULL;

	add_nod(&h_s, &h_l, ipt);

	lt_s = h_s;
	lt_l = h_l;

	while (lt_l != NULL)
	{
		dtsh->input = list_l->line;
		dtsh->args = st_line(dtsh->input);
		l = exe_line(dtsh);
		free(dtsh->args);

		if (l == 0)
			break;

		go_nt(&lt_s, &lt_l, dtsh);

		if (lt_l != NULL)
			lt_l = lt_l->next;
	}

	free_sep_lt(&h_s);
	free_line_lt(&h_l);

	if (l == 0)
		return (0);
	return (1);
}

/**
 * st_line - tokenizes the ipt str
 *
 * @ipt: ipt str.
 * Return: str splitted.
 */
char **st_line(char *ipt)
{
	size_t b_s;
	size_t i;
	char **tokens;
	char *t;

	b_s = TOK_BUFSIZE;
	tokens = malloc(sizeof(char *) * (b_s));
	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	t = _sttk(input, TOK_DELIM);
	tokens[0] = t;

	for (i = 1; t != NULL; i++)
	{
		if (i == b_s)
		{
			b_s += TOK_BUFSIZE;
			tokens = _reallocdp(tokens, i, sizeof(char *) * b_s);
			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		t = _sttk(NULL, TOK_DELIM);
		tokens[i] = t;
	}

	return (tokens);
}
