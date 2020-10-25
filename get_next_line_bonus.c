/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtanaka <jtanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 02:22:38 by jtanaka           #+#    #+#             */
/*   Updated: 2020/10/26 03:23:37 by jtanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line_bonus.h"

static int	join_save_save(char **line, char **save)
{
	char	*tmp;

	if (ft_strchr(*save, '\n'))
	{
		tmp = *line;
		*line = ft_substr(*save, 0, ft_strchr(*save, '\n') - *save);
		free(tmp);
		if (!(*line))
			return (ERROR);
		tmp = *save;
		*save = ft_substr(ft_strchr(*save, '\n') + 1, 0,
								ft_strlen(ft_strchr(*save, '\n')));
		free(tmp);
		if (!(*save))
			return (ERROR);
		return (SUCCESS);
	}
	else
	{
		tmp = *line;
		*line = *save;
		*save = NULL;
		free(tmp);
		return (CONTINUE_PROC);
	}
}

static int	split_by_newline(char **line, char **save, char *buf)
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
	if (!(*save = ft_substr(ft_strchr(buf, '\n') + 1, 0,
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

static int	read_process(int fd, char **line, char **save)
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
			ret = split_by_newline(line, save, buf);
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

t_save_list *new_lst(int fd)
{
	t_save_list *new_lst;
	
	if (!(new_lst = malloc(sizeof(t_save_list))))
		return (NULL);
	new_lst->fd = fd;
	new_lst->save = NULL;
	new_lst->next = NULL;
	return (new_lst);
}

void	lstadd_back(t_save_list **lst, t_save_list *new)
{
	t_save_list *lst_tmp;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	lst_tmp = *lst;
	while (lst_tmp->next)
		lst_tmp = lst_tmp->next;
	lst_tmp->next = new;
}

int			get_next_line(int fd, char **line)
{
	int					ret;
	static t_save_list	*save_list;
	t_save_list			*save_list_tmp;
	char				*save;  // fd が1024超えたらエラー出るから修正が必要

	if (fd < 0 || !line || BUFFER_SIZE <= 0 || !(*line = ft_strdup("")))
		return (ERROR);
	// search fd's t_list
	save_list_tmp = save_list;
	while (save_list_tmp)
	{
		if (save_list_tmp->fd == fd)
			break;
		save_list_tmp = save_list_tmp->next;
	}
	// If fd's t_list is found, save = save_t_list->save;
	// else it'll be created and add to save_list;
	if (!save_list_tmp)
	{
		printf("fd: %d save_list is not found\n", fd);
		if (!(save_list_tmp = new_lst(fd)))
			return (ERROR);
		lstadd_back(&save_list, save_list_tmp);
	}
	save = save_list_tmp->save;
	ret = CONTINUE_PROC;
	if (save)
		ret = join_save_save(line, &save);
	if (ret == CONTINUE_PROC)
		ret = read_process(fd, line, &save);
	return (ret);
}
