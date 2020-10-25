/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtanaka <jtanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 02:22:38 by jtanaka           #+#    #+#             */
/*   Updated: 2020/10/25 16:42:06 by jtanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	join_save_next_str(char **line, char **next_str)
{
	char	*tmp;

	if (ft_strchr(*next_str, '\n'))
	{
		tmp = *line;
		*line = ft_substr(*next_str, 0, ft_strchr(*next_str, '\n') - *next_str);
		free(tmp);
		if (!(*line))
			return (ERROR);
		tmp = *next_str;
		*next_str = ft_substr(ft_strchr(*next_str, '\n') + 1, 0,
								ft_strlen(ft_strchr(*next_str, '\n')));
		free(tmp);
		if (!(*next_str))
			return (ERROR);
		return (SUCCESS);
	}
	else
	{
		tmp = *line;
		*line = *next_str;
		*next_str = NULL;
		free(tmp);
		return (CONTINUE_PROC);
	}
}

static int	split_by_newline(char **line, char **next_str, char *buf)
{
	char	*old_line;
	char	*tmp;

	if (!(tmp = ft_substr(buf, 0, ft_strchr(buf, '\n') - buf)))
		return (ERROR);
	old_line = *line;
	if (!(*line = ft_strjoin(*line, tmp)))
	{
		free(old_line);
		free(tmp);
		return (ERROR);
	}
	free(old_line);
	free(tmp);
	if (!(*next_str = ft_substr(ft_strchr(buf, '\n') + 1, 0,
								ft_strlen(ft_strchr(buf, '\n')))))
		return (ERROR);
	return (SUCCESS);
}

static int	join_line_and_buf(char **line, char *buf)
{
	char	*tmp;

	tmp = *line;
	if (!(*line = ft_strjoin(*line, buf)))
	{
		free(tmp);
		return (ERROR);
	}
	free(tmp);
	return (CONTINUE_PROC);
}

static int	read_process(int fd, char **line, char **next_str)
{
	ssize_t		read_size;
	int			ret;
	char		*buf;

	ret = CONTINUE_PROC;
	if (!(buf = malloc(BUFFER_SIZE + 1)))
		return (ERROR);
	while (ret == CONTINUE_PROC && (read_size = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[read_size] = '\0';
		if (ft_strchr(buf, '\n'))
			ret = split_by_newline(line, next_str, buf);
		else
			ret = join_line_and_buf(line, buf);
	}
	free(buf);
	if (ret == CONTINUE_PROC && read_size == 0)
		ret = END_OF_FILE;
	else if (ret == CONTINUE_PROC && read_size == -1)
		ret = ERROR;
	return (ret);
}

int			get_next_line(int fd, char **line)
{
	int			ret;
	static char	*next_str[1024];  // fd が1024超えたらエラー出るから修正が必要

	if (fd < 0 || !line || BUFFER_SIZE <= 0 || !(*line = ft_strdup("")))
		return (ERROR);
	ret = CONTINUE_PROC;
	if (next_str[fd])
		ret = join_save_next_str(line, &next_str[fd]);
	if (ret == CONTINUE_PROC)
		ret = read_process(fd, line, &next_str[fd]);
	return (ret);
}