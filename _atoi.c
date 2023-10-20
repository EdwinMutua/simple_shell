
#include "shell.h"
/**
 * is_interactive - returns 1 if shell is interactive
 * @info: struct
 * Return: Return 1 if interactive otherwise 0
 */

int is_interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}
/**
 * is_delim - checks if character is a delimeter
 * @c: the char to check
 * @delim: the string delimeter
 * Return: if true,return 1, 0 if false
 */
int is_delim(char c, char *delim)
{
	while (*delim)
	{
		if (*delim++ == c)
			return (1);
	}
	return (0);
}
/**
 *_is_alpha - check alphabetic characters
 *@c: character to input
 *Return: Return 1 if  alphabet, 0 otherwise
 */
int _is_alpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}
/**
 *_atoi - converts string to integer
 *@s: the string to convert
 *Return: Return 0 if no nums in string
 */
int _atoi(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0;  s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
