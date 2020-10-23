/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtanaka <jtanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 00:15:26 by jtanaka           #+#    #+#             */
/*   Updated: 2020/10/23 21:28:08 by jtanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
dnakanoさんによると, ft_strjoin()などを駆使して書けばいいらしい.
*/

#include "get_next_line.h"
#include <stdio.h>
// #include "libft.h"  // あとで消す

int get_next_line(int fd, char **line)
{
	int status;  // return status
	ssize_t read_size;
	char *buf;
	char *current_str;  // 今回出力する文字列
	static char *next_str;  // 次使う文字列

	buf = malloc(BUFFER_SIZE + 1);
	*line = "";
	current_str = NULL;
	// *next_str に文字列が入っていたら(next_str[0] != '\0')それを *current_str に入れて *next_str を空にする
	if (next_str)
	{
		printf("\n*next_str に文字列が入っていたらそれを *current_str に入れて *next_str を空にする\n");
		current_str = ft_strdup(next_str);
		free(next_str);
		next_str = NULL;
	}
	
	// *current_str 内に改行が入っていたら改行までを *line にコピーして, 改行以降を *next_str に入れて return
	if (current_str && ft_strchr(current_str, '\n'))
	{
		printf("\n*current_str 内に改行が入っていたら改行までを *line にコピーして, 改行以降を *next_str に入れて return\n");
		*line = ft_substr(current_str, 0, ft_strchr(current_str, '\n') - current_str);
		next_str = ft_substr(ft_strchr(current_str, '\n') + 1, 0, ft_strlen(ft_strchr(current_str, '\n')));
		return (1);
	}

	// BUFFER_SIZE 読み込む
	buf[BUFFER_SIZE] = '\0';
	read_size = read(fd, buf, BUFFER_SIZE - 1);

	// if read() の返り値が0なら0を返す
	if (read_size == 0)
		return (0);

	// if read() の返り値が-1なら-1を返す
	if (read_size == -1)
		return (-1);

	// while (read_size > 0 && bufの中に改行が無い)
	while (read_size && !ft_strchr(buf, '\n'))
	{
		printf("\nif 改行が読み込んだ文字列内に無ければそれを*lineにそのまま strjoin(*line, buf) で入れる\n");
		*line = ft_strjoin(*line, buf);
		read_size = read(fd, buf, BUFFER_SIZE - 1);
	}

	// // if 改行が読み込んだ文字列内に無ければそれを*lineにそのまま strjoin(*line, buf) で入れる
	// if (!ft_strchr(buf, '\n'))
	// {
		
	// }
	
	// if 改行が来たらそれまでの文字列は *line に入れて,
	//    それ以降の文字列は *next_str に入れる
	if (ft_strchr(buf, '\n'))
	{
		printf("\nif 改行が来たらそれまでの文字列は *line に入れて,それ以降の文字列は *next_str に入れる\n");
		*line = ft_strjoin(*line, ft_substr(buf, 0, ft_strchr(buf, '\n') - buf));
		next_str = ft_substr(ft_strchr(buf, '\n') + 1, 0, ft_strlen(ft_strchr(buf, '\n')));
		return (1);
	}
}