#include "shell.h"

/**
 * bfree - Frees a pointer and sets it to NULL
 * @ptr: Address of the pointer to free
 *
 * This function frees the memory pointed to by 'ptr' and sets 'ptr' to NULL
 * to avoid a dangling pointer.
 *
 * Return: 1 if the pointer was freed, 0 otherwise.
 */
int bfree(void **ptr)
{
	if (ptr != NULL && *ptr != NULL)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

