/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtanaka <jtanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 00:15:26 by jtanaka           #+#    #+#             */
/*   Updated: 2020/10/23 20:34:37 by jtanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
dnakanoさんによると, ft_strjoin()などを駆使して書けばいいらしい.
*/

#include "get_next_line.h"
#include "libft.h"  // あとで消す

int get_next_line(int fd, char **line)
{
	int status;  // return status
	char buf[BUFFER_SIZE];
	char *current_str;  // 今回出力する文字列
	static char *next_str;  // 次使う文字列

	// *next_str に文字列が入っていたら(next_str[0] != '\0')それを *current_str に入れて *next_str を空にする
	if (next_str)
	{
		current_str = ft_strdup(next_str);
		free(next_str);
		next_str = NULL;
	}
	
	// *current_str 内に改行が入っていたら改行までを *line にコピーして, 改行以降を *next_str に入れて return
	if (ft_strchr(current_str, '\n'))
	{
		*line = ft_substr(current_str, 0, ft_strchr(current_str, '\n') - current_str);
		next_str = ft_substr(ft_strchr(current_str, '\n') + 1, 0, ft_strlen(ft_strchr(current_str, '\n')));
		return (1);
	}

	// BUFFER_SIZE 読み込む

	// if read() の返り値が0なら0を返す

	// if read() の返り値が-1なら-1を返す

	// if 改行が読み込んだ文字列内に無ければそれを*lineにそのまま strjoin(*line, buf) で入れる
	
	// if 改行が来たらそれまでの文字列は *line に入れて,
	//    それ以降の文字列は *next_str に入れる

}