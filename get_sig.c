#include "shell.h"

/**
 * get_sig - Handle the crtl + c call in promp
 * @s: Sig handler
 */
void get_sig(int s)
{
	(void)s:;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}
