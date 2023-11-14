#include "shell.h"

/**
 * _memcp - copies info btwn void ptr.
 * @nptr: dest ptr.
 * @ptr: src pointer.
 * @s: size of the new ptr.
 *
 * Return: no return.
 */
void _memcp(void *nptr, const void *ptr, unsigned int s)
{
	char *char_ptr = (char *)ptr;
	char *char_nptr = (char *)nptr;
	unsigned int a;

	for (a = 0; a < size; a++)
		char_nptr[a] = char_ptr[a];
}

/**
 * _reloc - reallocates  mem block.
 * @ptr: ptr to the mem previously allocated.
 * @o_s: size, in bytes, of the allocated space of ptr.
 * @n_s: new size, in bytes, of the new memory block.
 *
 * Return: ptr.
 * if n_s == o_s, returns ptr without changes.
 * if malloc fails, returns NULL.
 */
void *_reloc(void *ptr, unsigned int o_s, unsigned int n_s)
{
	void *nptr;

	if (ptr == NULL)
		return (malloc(n_s));

	if (n_s == 0)
	{
		free(ptr);
		return (NULL);
	}

	if (n_s == o_s)
		return (ptr);

	nptr = malloc(n_s);
	if (nptr == NULL)
		return (NULL);

	if (n_s < o_s)
		_memcp(nptr, ptr, n_s);
	else
		_memcp(nptr, ptr, o_s);

	free(ptr);
	return (nptr);
}

/**
 * _relocdp - reallocates a mem block of a double ptr.
 * @ptr: double ptr to the memory previously allocated.
 * @o_s: size, in bytes, of the allocated space of ptr.
 * @n_s: new size, in bytes, of the new memory block.
 *
 * Return: ptr.
 * if n_s == o_s, returns ptr without changes.
 * if malloc fails, returns NULL.
 */
char **_relocdp(char **ptr, unsigned int o_s, unsigned int n_s)
{
	char **nptr;
	unsigned int a;

	if (ptr == NULL)
		return (malloc(sizeof(char *) * n_s));

	if (n_s == o_s)
		return (ptr);

	nptr = malloc(sizeof(char *) * n_s);
	if (nptr == NULL)
		return (NULL);

	for (a = 0; a < o_s; a++)
		nptr[a] = ptr[a];

	free(ptr);

	return (nptr);
}
