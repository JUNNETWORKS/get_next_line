/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtanaka <jtanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 00:15:26 by jtanaka           #+#    #+#             */
/*   Updated: 2020/10/24 18:24:00 by jtanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int get_next_line(int fd, char **line)
{
	ssize_t read_size;
	char *buf;
	char *tmp;
	char *old_line;  // free() 用
	static char *next_str;  // 次使う文字列

	buf = malloc(BUFFER_SIZE + 1);  // ヒープ領域に確保する必要ある?
	*line = malloc(1);
	*line[0] = '\0';
	tmp = NULL;
	old_line = NULL;
	if (next_str)
	{
		// TODO: ここを関数に切り出す
		if (ft_strchr(next_str, '\n'))  // *next_str 内に改行が入っていたら改行までを *line にコピーして, 改行以降を *next_str に入れて return
		{
			old_line = *line;
			if (!(*line = ft_substr(next_str, 0, ft_strchr(next_str, '\n') - next_str)))
			{
				free(old_line);
				free(buf);
				return (-1);
			}
			free(old_line);
			tmp = next_str;
			if (!(next_str = ft_substr(ft_strchr(next_str, '\n') + 1, 0, ft_strlen(ft_strchr(next_str, '\n')))))
			{
				free(tmp);
				free(buf);
				return (-1);
			}
			free(tmp);
			free(buf);
			return (1);
		}
		else  // next_str 内に改行が入っていない
		{
			old_line = *line;
			*line = next_str;
			next_str = NULL;
			free(old_line);	
		}
	}

	// 改行が出現するまで読み込んで繋げる.
	// 改行が出現したらそれまでの文字列を*lineに入れて, それ以降の文字列を*next_strに入れる
	while ((read_size = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[read_size] = '\0';
		// if 改行が来たらそれまでの文字列は *line に入れて,
		//    それ以降の文字列は *next_str に入れる
		if (ft_strchr(buf, '\n'))
		{
			// TODO: ここを関数に切り出す
			if (!(tmp = ft_substr(buf, 0, ft_strchr(buf, '\n') - buf)))
			{
				free(buf);
				return (-1);
			}
			old_line = *line;
			if (!(*line = ft_strjoin(*line, tmp)))
			{
				free(old_line);
				free(tmp);
				return (-1);
			}
			free(old_line);
			free(tmp);
			if (!(next_str = ft_substr(ft_strchr(buf, '\n') + 1, 0, ft_strlen(ft_strchr(buf, '\n')))))
			{
				free(buf);
				return (-1);
			}
			free(buf);
			return (1);
		}
		else
		{
			old_line = *line;
			if (!(*line = ft_strjoin(*line, buf)))
			{
				free(old_line);
				free(buf);
				return (-1);
			}
			free(old_line);
		}
	}
	free(buf);
	if (read_size == 0)
		return (0);
	else
		return (-1);
}
