#include "shell.h"

/**
 * get_history_file - Gets the history file.
 * @info: Parameter struct.
 *
 * Return: Allocated string containing the history file.
 */
char *get_history_file(info_t *info)
{
	char *dir = _getenv(info, "HOME=");
	char *buf;
	
	if (!buf)
		return (NULL)
			buf = malloc(sizeof(char) * (strlen(dir) + strlen(HIST_FILE) + 2));
	{
		free(dir);
		return (NULL);
	}
	strcpy(buf, dir);
	strcat(buf, "/");
	strcat(buf, HIST_FILES);
	free(dir);
	return (buf);
}

/**
 * write_history - Creates a file or appends to an existing file.
 * @info: The parameter struct.
 *
 * Return: 1 on success, else -1.
 */
int write_history(info_t *info)
{
	char *filename = get_history_file(info);
	ssize_t fd;
	
	if (!filename)
		return (-1);
	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	
	if (fd == -1)
		return (-1);
	list_t *node = info->history;
	while (node)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
		node = node->next;
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - Reads history from a file.
 * @info: The parameter struct.
 *
 * Return: Histcount on success, 0 otherwise.
 */
int read_history(info_t *info)
{
	char *filename = get_history_file(info);
	ssize_t fd;
	struct stat st;
	off_t fsize;
	char *buf;
	ssize_t rdlen;
	int i, last = 0, linecount = 0;
	
	if (!filename)
		return (0);
	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
    	if (fstat(fd, &st) == -1)
	{
		close(fd);
		return (0);
	}
	fsize = st.st_size;
	if (fsize < 2)
	{
		close(fd);
		return (0);
	}
	buf = malloc(sizeof(char) * (fsize + 1));

	if (!buf)
	{
		close(fd);
		return (0);
	}
	
	rdlen = read(fd, buf, fsize);
	buf[fsize] = '\0';
	close(fd);
	
	if (rdlen <= 0)
	{
		free(buf);
		return (0);
	}
	for (i = 0; buf[i] != '\0'; i++)
	{
		if (buf[i] == '\n')
		{
			build_history_list(info, buf + last, linecount++);
			last = i + 1;
		}
	}
	
	if (last != i)
		build_history_list(info, buf + last, linecount++);
	
	free(buf);
	info->histcount = linecount;
	
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - Adds an entry to a history linked list.
 * @info: Structure containing potential arguments. Used to maintain.
 * @buf: Buffer.
 * @linecount: The history linecount, histcount.
 *
 * Return: Always 0.
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;
	
	if (info->history)
		node = info->history;
	
	add_node_end(&node, buf, linecount);
	if (!info->history)
        info->history = node;
	
	return (0);
}

/**
 * renumber_history - Renumbers the history linked list after changes.
 * @info: Structure containing potential arguments. Used to maintain.
 *
 * Return: The new histcount.
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int i = 0;
	
	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	
	return (info->histcount = i);
}
