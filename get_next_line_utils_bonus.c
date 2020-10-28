/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtanaka <jtanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 02:22:55 by jtanaka           #+#    #+#             */
/*   Updated: 2020/10/28 18:09:24 by jtanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	ans;

	ans = 0;
	while (s[ans])
		ans++;
	return (ans);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substr;
	size_t			i;
	size_t			s_len;

	if (!(substr = malloc(len + 1)))
		return (NULL);
	*substr = '\0';
	if (start >= ft_strlen(s))
		return (substr);
	i = 0;
	s_len = ft_strlen(s);
	while (i < len && i < s_len)
	{
		substr[i] = *(s + start + i);
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

char	*ft_strchr(const char *s, int c)
{
	char	*str;

	if (!s)
		return (NULL);
	str = (char*)s;
	while (*str || !c)
	{
		if (*str == (char)c)
			return (str);
		str++;
	}
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*str;
	char			*ans;
	size_t			s1_len;
	size_t			s2_len;
	unsigned int	total_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (!s1 && !s2)
		return (NULL);
	if (s1 && !s2)
		// return (ft_strdup(s1));
		return (ft_substr(s1, 0, s1_len));
	if (!s1 && s2)
		// return (ft_strdup(s2));
		return (ft_substr(s2, 0, s2_len));
	total_len = s1_len + ft_strlen(s2);
	if (!(str = malloc(total_len + 1)))
		return (NULL);
	ans = str;
	while (*s1)
		*str++ = *s1++;
	while (*s2)
		*str++ = *s2++;
	*str = '\0';
	return (ans);
}

t_list	*search_fd_elem(t_list *lst, int fd)
{
	while (lst)
	{
		if (lst->fd == fd)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

t_list	*create_fd_elem(t_list **lst, int fd, size_t save_size)
{
	t_list *new;

	if (!lst)
		return (NULL);
	if (!(new = malloc(sizeof(t_list))))
		return (NULL);
	if (!(new->save = malloc(save_size)))
	{
		free(new);
		return (NULL);
	}
	new->fd = fd;
	// 新しく作成した要素は先頭に繋げる
	new->previous = NULL;
	if (!(*lst))
	{
		*lst = new;
		new->next = NULL;
	}
	else
	{
		new->next = *lst;
		*lst = new;	
	}
	return (new);
}

void		delete_fd_elem(t_list **lst, int fd)
{
	t_list *fd_elem;
	
	if (!lst)
		return ;
	if (fd >= 0)
	{
		if (!(fd_elem = search_fd_elem(*lst, fd)))
			return ;
		free(fd_elem->save);
		if (fd_elem->previous)
			fd_elem->previous->next = fd_elem->next;
		else
			*lst = fd_elem->next;
		free(fd_elem);
	}
	// マイナスの時は delete all
	else
	{
		while (*lst)
		{
			fd_elem = *lst;
			free(fd_elem->save);
			*lst = fd_elem->next;
			free(fd_elem);
		}
	}
}
