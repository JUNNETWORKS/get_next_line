/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtanaka <jtanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 00:15:26 by jtanaka           #+#    #+#             */
/*   Updated: 2020/10/24 23:43:02 by jtanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int join_save_next_str(char **line, char **next_str)
{
	char *tmp;
	
	if (ft_strchr(*next_str, '\n'))  // *next_str 内に改行が入っていたら改行までを *line にコピーして, 改行以降を *next_str に入れて return
	{
		tmp = *line;
		*line = ft_substr(*next_str, 0, ft_strchr(*next_str, '\n') - *next_str);
		free(tmp);
		if (!(*line))
			return (ERROR);
		tmp = *next_str;
		*next_str = ft_substr(ft_strchr(*next_str, '\n') + 1, 0, ft_strlen(ft_strchr(*next_str, '\n')));
		free(tmp);
		if (!(*next_str))
			return (ERROR);
		return (SUCCESS);
	}
	else  // *next_str 内に改行が入っていない
	{
		tmp = *line;
		*line = *next_str;
		*next_str = NULL;
		free(tmp);
		return (CONTINUE_PROCESS);
	}
}

int split_by_newline(char **line, char **next_str, char *buf)
{
	char *old_line;
	char *tmp;
	
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
	if (!(*next_str = ft_substr(ft_strchr(buf, '\n') + 1, 0, ft_strlen(ft_strchr(buf, '\n')))))
		return (ERROR);
	return (SUCCESS);
}

int get_next_line(int fd, char **line)
{
	ssize_t read_size;
	int status;
	char *buf;
	char *tmp;
	static char *next_str;  // 次使う文字列

	buf = malloc(BUFFER_SIZE + 1);  // ヒープ領域に確保する必要ある?
	*line = malloc(1);
	*line[0] = '\0';
	tmp = NULL;
	status = CONTINUE_PROCESS;
	if (next_str)
		status = join_save_next_str(line, &next_str);// TODO: 返り値をどうするか
	// 改行が出現するまで読み込んで繋げる.
	// 改行が出現したらそれまでの文字列を*lineに入れて, それ以降の文字列を*next_strに入れる
	while (status == CONTINUE_PROCESS && (read_size = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[read_size] = '\0';
		// if 改行が来たらそれまでの文字列は *line に入れて,
		//    それ以降の文字列は *next_str に入れる
		if (ft_strchr(buf, '\n'))
			status = split_by_newline(line, &next_str, buf);
		else
		{
			tmp = *line;
			if (!(*line = ft_strjoin(*line, buf)))
				status = ERROR;
			free(tmp);
		}
	}
	free(buf);
	if (read_size == 0)
		status = END_OF_FILE;
	else if (read_size == -1)
		status = ERROR;
	return (status);
}
