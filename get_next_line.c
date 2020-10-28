/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtanaka <jtanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 00:15:26 by jtanaka           #+#    #+#             */
/*   Updated: 2020/10/28 18:12:10 by jtanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	join_line_and_save(char **line, char **save)
{
	char	*tmp;
	char	*newline_ptr;

	if ((newline_ptr = ft_strchr(*save, '\n')))
	{
		tmp = *line;
		*line = ft_substr(*save, 0, newline_ptr - *save);
		free(tmp);
		if (!(*line))
			return (ERROR);
		tmp = *save;
		*save = ft_substr(newline_ptr + 1, 0, ft_strlen(newline_ptr + 1));
		free(tmp);
		if (!(*save))
			return (ERROR);
		return (SUCCESS);
	}
	else
	{
		tmp = *line;
		*line = *save;
		*save = NULL;
		free(tmp);
		return (CONTINUE_READ);
	}
}

static int	split_by_newline(char **line, char **save, char *buf)
{
	char	*old_line;
	char	*tmp;
	char	*newline_ptr;

	newline_ptr = ft_strchr(buf, '\n');
	if (!(tmp = ft_substr(buf, 0, newline_ptr - buf)))
		return (ERROR);
	old_line = *line;
	*line = ft_strjoin(*line, tmp);
	free(old_line);
	free(tmp);
	if (!(*line))
		return (ERROR);
	if (!(*save = ft_substr(newline_ptr + 1, 0,
								ft_strlen(newline_ptr + 1))))
		return (ERROR);
	return (SUCCESS);
}

static int	join_line_and_buf(char **line, char *buf)
{
	char	*tmp;

	tmp = *line;
	*line = ft_strjoin(*line, buf);
	free(tmp);
	if (!(*line))
		return (ERROR);
	return (CONTINUE_READ);
}

static int	read_process(int fd, char **line, char **save)
{
	ssize_t		read_size;
	int			ret;
	char		*buf;

	ret = CONTINUE_READ;
	if (!(buf = malloc(BUFFER_SIZE + 1)))
		return (ERROR);
	while (ret == CONTINUE_READ && (read_size = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[read_size] = '\0';
		if (ft_strchr(buf, '\n'))
			ret = split_by_newline(line, save, buf);
		else
			ret = join_line_and_buf(line, buf);
	}
	free(buf);
	if (ret == CONTINUE_READ && read_size == 0)
		ret = END_OF_FILE;
	else if (ret == CONTINUE_READ && read_size == -1)
		ret = ERROR;
	return (ret);
}

int			get_next_line(int fd, char **line)
{
	int			ret;
	static char	*save;

	if (fd < 0 || !line || BUFFER_SIZE <= 0 || !(*line = ft_strdup("")))
		return (ERROR);
	ret = CONTINUE_READ;
	if (save)
		ret = join_line_and_save(line, &save);
	if (ret == CONTINUE_READ)
		ret = read_process(fd, line, &save);
	return (ret);
}
