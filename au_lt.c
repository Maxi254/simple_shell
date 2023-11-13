#include "shell.h"

/**
 * add_sep_nod_end - puts a sep to the end
 * @hd: hd of the ll.
 * @sep: separator found (; | &).
 * Return: add of the head.
 */
sepa_list *add_sep_nod_end(sepa_list **hd, char sep)
{
	sepa_list *n, *t;

	n = malloc(sizeof(sepa_list));
	if (n == NULL)
		return (NULL);

	n->septr = sep;
	n->next = NULL;
	t = *hd;

	if (t == NULL)
	{
		*hd = n;
	}
	else
	{
		while (t->next != NULL)
			t = t->next;
		t->next = n;
	}

	return (*hd);
}

/**
 * free_sep_lt - frees  sep_lt
 * @head: hd of the ll
 * Return: no return.
 */
void free_sep_lt(sepa_list **hd)
{
	sepa_list *t;
	sepa_list *c;

	if (hd != NULL)
	{
		c = *hd;
		while ((t = c) != NULL)
		{
			c = c->next;
			free(t);
		}
		*hd = NULL;
	}
}

/**
 * add_line_nod_end - adds a cmd line at the end of the ll
 * @hd: hd of the ll
 * @line: cmd line.
 * Return: add of the hd.
 */
line_list *add_line_node_end(line_list **hd, char *line)
{
	line_list *n, *t;

	n = malloc(sizeof(line_list));
	if (n == NULL)
		return (NULL);

	n->line = line;
	n->next = NULL;
	t = *hd;

	if (t == NULL)
	{
		*hd = n;
	}
	else
	{
		while (t->next != NULL)
			t = t->next;
		t->next = n;
	}

	return (*hd);
}

/**
 * free_line_lt - frees ll
 * @hd: hd of the ll.
 * Return: no return.
 */
void free_line_lt(line_list **hd)
{
	line_list *t;
	line_list *c;

	if (hd != NULL)
	{
		c = *hd;
		while ((t = c) != NULL)
		{
			c = c->next;
			free(t);
		}
		*hd = NULL;
	}
}
