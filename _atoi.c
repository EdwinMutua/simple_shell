#include "shell.h"

/**
 * is_interactive - Check if shell is in interactive mode.
 * @info: Pointer to struct info_t.
 *
 * Return: 1 if in interactive mode, 0 otherwise.
 */
int is_interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delimiter - Check if a character is a delimiter.
 * @c: The character to check.
 * @delim: The delimiter string.
 *
 * Return: 1 if it's a delimiter, 0 if not.
 */
int is_delimiter(char c, char *delim)
{
	while (*delim)
	{
		if (*delim++ == c)
		{
			return (1);
		}
	}
	return (0);
}

/**
 * is_alpha - Check if a character is alphabetic.
 * @c: The character to check.
 *
 * Return: 1 if it's alphabetic, 0 otherwise.
 */
int is_alpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

/**
 * string_to_int - Convert a string to an integer.
 * @s: The string to be converted.
 *
 * Return: 0 if no numbers in string, the converted number otherwise.
 */
int string_to_int(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
		{
			sign *= -1;
		}

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
		{
			flag = 2;
		}
	}

	if (sign == -1)
	{
		output = -result;
	}
	else
	{
		output = result;
	}

	return (output);
}

