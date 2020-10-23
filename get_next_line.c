/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtanaka <jtanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 00:15:26 by jtanaka           #+#    #+#             */
/*   Updated: 2020/10/24 00:47:46 by jtanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
通ってないテスト
test/long_line.txt  BUF=64
test/64bit_line.txt  BUF=63
test/long_line.txt  BUF=63
test/long_line.txt  BUF=65
test/long_line.txt  BUF=100
test/long_line.txt  BUF=9999
*/

#include "get_next_line.h"
#include <stdio.h>

int get_next_line(int fd, char **line)
{
	// int status;  // return status
	ssize_t read_size;
	char *buf;
	char *tmp;
	char *old_line;  // free() 用
	static char *next_str;  // 次使う文字列

	// printf("\nnext_str: %s \t %p\n", next_str, next_str);

	buf = malloc(BUFFER_SIZE + 1);  // ヒープ領域に確保する必要ある?
	*line = malloc(1);
	*line[0] = '\0';
	tmp = NULL;
	old_line = NULL;

	// *next_str 内に改行が入っていたら改行までを *line にコピーして, 改行以降を *next_str に入れて return
	if (next_str && ft_strchr(next_str, '\n'))
	{
		// printf("\n*next_str 内に改行が入っていたら改行までを *line にコピーして, 改行以降を *next_str に入れて return\n");
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
	// next_str 内に改行が入っていない
	else if (next_str && !ft_strchr(next_str, '\n'))
	{
		old_line = *line;
		*line = next_str;
		free(old_line);
	}

	// BUFFER_SIZE 読み込む
	read_size = read(fd, buf, BUFFER_SIZE);
	buf[read_size] = '\0';
	// printf("read(fd, buf, BUFFER_SIZE)の返り値: %ld\n", read_size);
	// printf("buf[] の中身: %s\n", buf);

	// if read() の返り値が0なら0を返す
	if (read_size == 0)
	{
		free(buf);
		return (0);
	}

	// if read() の返り値が-1なら-1を返す
	if (read_size == -1)
	{
		free(buf);
		return (-1);
	}

	// while (read_size > 0 && bufの中に改行が無い)
	while (read_size > 0 && !ft_strchr(buf, '\n'))
	{
		// printf("\nif 改行が読み込んだ文字列内に無ければそれを*lineにそのまま strjoin(*line, buf) で入れる\n");
		old_line = *line;
		if (!(*line = ft_strjoin(*line, buf)))
		{
			free(old_line);
			free(buf);
			return (-1);
		}
		free(old_line);
		read_size = read(fd, buf, BUFFER_SIZE);
		buf[read_size] = '\0';
		// printf("read(fd, buf, BUFFER_SIZE)の返り値: %ld\n", read_size);
		// printf("buf[] の中身: %s\n", buf);
	}

	// if 改行が来たらそれまでの文字列は *line に入れて,
	//    それ以降の文字列は *next_str に入れる
	if (read_size > 0)
	{
		// printf("\nif 改行が来たらそれまでの文字列は *line に入れて,それ以降の文字列は *next_str に入れる\n");
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
	free(buf);
	return (0);
}