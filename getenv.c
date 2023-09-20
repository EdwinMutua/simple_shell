#include "shell.h"

/**
 * get_environ - Returns a copy of the environment variables.
 * @info: Structure containing potential arguments.
 * Return: A copy of the environment variables.
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - Remove an environment variable.
 * @info: Structure containing potential arguments.
 * @var: The environment variable to remove.
 * Return: 1 on success (variable removed), 0 otherwise.
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;

	if (!node || !var)
		return (0);

	while (node)
	{
		if (starts_with(node->str, var) && node->str[strlen(var)] == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), i);
			i = 0;
			node = info->env;
		}
		else
		{
			node = node->next;
			i++;
		}
	}
	return (info->env_changed);
}

/**
 * _setenv - Initialize a new environment variable or modify an existing one.
 * @info: Structure containing potential arguments.
 * @var: The environment variable to set or modify.
 * @value: The value to set for the environment variable.
 * Return: 0 on success, 1 on failure.
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;

	if (!var || !value)
		return (1);

	buf = malloc(strlen(var) + strlen(value) + 2);
	if (!buf)
		return (1);

	sprintf(buf, "%s=%s", var, value);

	node = info->env;
	while (node)
	{
		if (starts_with(node->str, var) && node->str[strlen(var)] == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}

	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}

