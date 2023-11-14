#include "shell.h"

/**
 * add_rvar_node - ads a var to the end
 * @hd: hd of the ll
 * @l_var: lens of the var
 * @val: val of the var
 * @lens_val: l
 * Return: address of the head.
 */
rvar *add_rvar_node(rvar **hd, int l_var, char *val, int l_val)
{
	rvar *n, *t;

	n = malloc(sizeof(rvar));
	if (n == NULL)
		return (NULL);

	n->len_var = l_var;
	n->val = val;
	n->len_val = l_val;

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
 * free_rvar_list - frees  rvar list
 * @hd: hd of the ll.
 * Return: no return.
 */
void free_rvar_list(rvar **hd)
{
	rvar *t;
	rvar *c;

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
