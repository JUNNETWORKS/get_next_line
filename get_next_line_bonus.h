/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtanaka <jtanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 02:22:45 by jtanaka           #+#    #+#             */
/*   Updated: 2020/10/28 17:57:18 by jtanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

# define SUCCESS		1
# define END_OF_FILE	0
# define ERROR			-1
# define CONTINUE_READ	-2
# define FD_MAX 4096

# ifndef BUFFER_SIZE
# 	define BUFFER_SIZE 256
# endif

typedef struct	s_list
{
	int				fd;
	char			*save;
	struct s_list	*previous;
	struct s_list	*next;
}	t_list;


int		get_next_line(int fd, char **line);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
t_list	*create_fd_elem(t_list **lst, int fd, size_t save_size);
t_list	*search_fd_elem(t_list *lst, int fd);
void	delete_fd_elem(t_list **lst, int fd);

#endif
