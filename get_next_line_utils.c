/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtanaka <jtanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 00:53:53 by jtanaka           #+#    #+#             */
/*   Updated: 2020/10/21 02:11:15 by jtanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	unsigned int ans;

	ans = 0;
	while (s[ans])
		ans++;
	return (ans);
}


char	*ft_strdup(const char *s)
{
	unsigned int	s_len;
	char			*new_str;
	unsigned int	i;

	s_len = ft_strlen(s);
	if (!(new_str = (char*)malloc(s_len + 1)))
		return (NULL);
	i = 0;
	while (i < s_len)
	{
		new_str[i] = s[i];
		i++;
	}
	new_str[s_len] = '\0';
	return (new_str);
}


t_list	*ft_lstnew(char *str)
{
	t_list *new_list;

	new_list = (t_list*)malloc(sizeof(t_list));
	if (!new_list)
		return (NULL);
	new_list->str = str;
	new_list->next = NULL;
	return (new_list);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list *lst_tmp;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	lst_tmp = *lst;
	while (lst_tmp->next != NULL)
		lst_tmp = lst_tmp->next;
	lst_tmp->next = new;
}

// リストの先頭要素のポインタを返す
t_list	*ft_lstadd_str_back(t_list **lst, char *str)
{
	t_list *new_elem;
	t_list *lst_tmp;

	if (!lst || !str)
		return (NULL);
	if (!(new_elem = ft_lstnew(ft_strdup(str))))
		return (NULL);
	if (!*lst)
	{
		*lst = new_elem;
		return ;
	}
	lst_tmp = *lst;
	while (lst_tmp->next != NULL)
		lst_tmp = lst_tmp->next;
	lst_tmp->next = new_elem;
	return (*lst);
}

int	ft_lstsize(t_list *lst)
{
	int	size;

	if (!lst)
		return (0);
	size = 0;
	while (lst)
	{
		lst = lst->next;
		size++;
	}
	return (size);
}

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstclear(t_list **lst)
{
	t_list	*lst_tmp;
	t_list	*previous;

	lst_tmp = *lst;
	while (lst_tmp)
	{
		free(lst_tmp->str);
		previous = lst_tmp;
		lst_tmp = lst_tmp->next;
		free(previous);
	}
	*lst = NULL;
}