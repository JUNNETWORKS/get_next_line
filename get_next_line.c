/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtanaka <jtanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 00:15:26 by jtanaka           #+#    #+#             */
/*   Updated: 2020/10/21 02:17:18 by jtanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *generate_str_from_lst(t_list **str_list);

int get_idx(char *buf, char c)
{
	int i;
	
	i = 0;
	while (buf[i])
	{
		if (buf[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	get_next_line(int fd, char **line)
{
	int i;
	int idx;
	static char buf[BUFFER_SIZE];
	
	// ファイルから BUFFER_SIZE 読み込み
	read(fd, buf, BUFFER_SIZE - 1);
	buf[BUFFER_SIZE - 1] = '\0';
	
	i = 0;
	// (改行||EOF) があった場合
	if ((idx = get_idx(buf, '\0')) >= 0)
	{
		if (!(*line = malloc(idx + 1)))
			return (-1);
		while (i < idx)
			*line[i] = buf[i++];
		*line[i] = '\0';
		return (1);
	}
	// (改行||EOF) が無かった場合
	else
	{
		// bufで連結リストを作成
		t_list *str_list;
		if(!(str_list = ft_lstadd_str_back(&str_list, buf)))
			return (NULL);
		// ft_lstadd_back(&str_list, ft_lstnew(ft_strdup(buf)));
		read(fd, buf, BUFFER_SIZE - 1);
		while (get_idx(buf, '\n') || get_idx(buf, EOF))
		{
			if(!(str_list = ft_lstadd_str_back(&str_list, buf)))
			{
				ft_lstclear(&str_list);
				return(NULL);
			}
			// ft_lstadd_back(&str_list, ft_lstnew(ft_strdup(buf)));
			read(fd, buf, BUFFER_SIZE - 1);
		}
		// ft_lstadd_back(&str_list, ft_lstnew(ft_strdup(buf)));
		str_list = ft_lstadd_str_back(&str_list, buf);

		// 連結リストから文字列を生成する
		*line = generate_str_from_lst(&str_list);
		return (1);
	}
}

char *generate_str_from_lst(t_list **str_list)
{
	unsigned int	str_len;
	char			*str;
	char			*str_tmp;
	t_list			*lst_tmp;

	// (連結リストの個数 - 1) * (BUFFER_SIZE - 1) + 最後の要素の改行までの文字数 をmalloc()で確保
	str_len = (ft_lstsize(*str_list) - 1) * (BUFFER_SIZE - 1);
	str_len += ft_strlen(ft_lstlast(*str_list)->str);
	if (!(str = (char*)malloc(str_len + 1)))
		return (NULL);
	
	// 連結リストから文字列を生成
	lst_tmp = *str_list;
	str_tmp = str;
	while (lst_tmp)
	{
		while (*lst_tmp->str && *lst_tmp->str != '\n' && *lst_tmp->str != EOF)
			*str_tmp++ = *lst_tmp->str++;
		lst_tmp = lst_tmp->next;
	}
	*str_tmp = '\0';
	return (str);
}