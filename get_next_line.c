/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtanaka <jtanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 00:15:26 by jtanaka           #+#    #+#             */
/*   Updated: 2020/10/23 22:19:59 by jtanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
dnakanoさんによると, ft_strjoin()などを駆使して書けばいいらしい.
*/

#include "get_next_line.h"
#include <stdio.h>

int get_next_line(int fd, char **line)
{
	int status;  // return status
	ssize_t read_size;
	char *buf;
	char *tmp;  // 今回出力する文字列
	char *tmp_line;
	static char *next_str;  // 次使う文字列

	printf("\nnext_str: %s \t %p\n", next_str, next_str);

	buf = malloc(BUFFER_SIZE + 1);
	*line = malloc(1);
	*line[0] = '\0';
	tmp = NULL;
	// *next_str に文字列が入っていたら(next_str[0] != '\0')それを *tmp に入れて *next_str を空にする
	if (next_str)
	{
		printf("\n*next_str に文字列が入っていたらそれを *tmp に入れて *next_str を空にする\n");
		tmp = ft_strdup(next_str);
		free(next_str);
		next_str = NULL;
	}
	
	// *tmp 内に改行が入っていたら改行までを *line にコピーして, 改行以降を *next_str に入れて return
	if (tmp && ft_strchr(tmp, '\n'))
	{
		printf("\n*tmp 内に改行が入っていたら改行までを *line にコピーして, 改行以降を *next_str に入れて return\n");
		tmp_line = *line;
		*line = ft_substr(tmp, 0, ft_strchr(tmp, '\n') - tmp);
		free(tmp_line);
		next_str = ft_substr(ft_strchr(tmp, '\n') + 1, 0, ft_strlen(ft_strchr(tmp, '\n')));
		free(tmp);
		free(buf);
		return (1);
	}
	free(tmp);

	// BUFFER_SIZE 読み込む
	read_size = read(fd, buf, BUFFER_SIZE);
	buf[read_size] = '\0';
	printf("read(fd, buf, BUFFER_SIZE)の返り値: %ld\n", read_size);
	printf("buf[] の中身: %s\n", buf);

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
	while (read_size && !ft_strchr(buf, '\n'))
	{
		printf("\nif 改行が読み込んだ文字列内に無ければそれを*lineにそのまま strjoin(*line, buf) で入れる\n");
		tmp_line = *line;
		*line = ft_strjoin(*line, buf);
		free(tmp_line);
		read_size = read(fd, buf, BUFFER_SIZE);
		printf("read(fd, buf, BUFFER_SIZE)の返り値: %ld\n", read_size);
		printf("buf[] の中身: %s\n", buf);
	}

	// // 最後改行が無いファイルの場合はそこまでの分を返す
	// if (read_size == 0)
	// 	return (1);

	// if 改行が来たらそれまでの文字列は *line に入れて,
	//    それ以降の文字列は *next_str に入れる
	if (read_size && ft_strchr(buf, '\n'))
	{
		printf("\nif 改行が来たらそれまでの文字列は *line に入れて,それ以降の文字列は *next_str に入れる\n");
		tmp = ft_substr(buf, 0, ft_strchr(buf, '\n') - buf);
		tmp_line = *line;
		*line = ft_strjoin(*line, tmp);
		free(tmp_line);
		free(tmp);
		next_str = ft_substr(ft_strchr(buf, '\n') + 1, 0, ft_strlen(ft_strchr(buf, '\n')));
		free(buf);
		return (1);
	}
	free(buf);
	return (0);
}